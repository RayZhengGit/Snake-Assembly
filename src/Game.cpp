#include "Game.h"
#include <Timer.h>
#include <PerformanceTracker.h>
#include <EventSystem.h>
#include <InputSystem.h>
#include "GameEvents.h"
#include <ctime>
#include "MainMenu.h"
#include "MapMenu.h"
#include "OptionsMenu.h"
#include "EscapeMenu.h"
#include "ResultScreen.h"
#include <fstream>
#include <sstream>
#include <unordered_map>

Game* Game::mInstance = new Game;

Game* Game::getInstance()
{
	return mInstance;
}

void Game::init(unsigned int width, unsigned int height, unsigned int framesPerSecond)
{
	srand(time(NULL));

	EventSystem::getInstance()->addListener((EventType)MOVE_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)COLLISION_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)DISPLAY_ESCAPE_MENU_EVENT, this);

	loadWords();
	mpSystem->init(width, height);
	mpGraphicsBufferManager->addGraphicsBuffer("Background", new GraphicsBuffer(ASSET_PATH + GAMEPLAY_BACKGROUND_FILENAME));
	mpGraphicsBufferManager->addGraphicsBuffer("Snake Graphics", new GraphicsBuffer(ASSET_PATH + SNAKE_GRAPHICS_FILENAME));
	mpGraphicsBufferManager->addGraphicsBuffer("Purple Portal", new GraphicsBuffer(ASSET_PATH + PURPLE_PORTAL_FILENAME));
	mpGraphicsBufferManager->addGraphicsBuffer("Blue Portal", new GraphicsBuffer(ASSET_PATH + BLUE_PORTAL_FILENAME));
	mpGraphicsBufferManager->addGraphicsBuffer("Red Portal", new GraphicsBuffer(ASSET_PATH + RED_PORTAL_FILENAME));
	mpGraphicsBufferManager->addGraphicsBuffer("Snail", new GraphicsBuffer(ASSET_PATH + SNAIL_FILENAME));
	mpGraphicsBufferManager->addGraphicsBuffer("Ghost", new GraphicsBuffer(ASSET_PATH + GHOST_FILENAME));
	mpGraphicsBufferManager->addGraphicsBuffer("Rock", new GraphicsBuffer(ASSET_PATH + ROCK_FILENAME));
	mpInputTranslator->init();
	mpMapMenu->init();
	mpOptionsMenu->init();
	mpMainMenu->init();
	mpEscapeMenu->init();
	mpResultScreen->init();
	mpSoundSystem->init();
	mpHud->init(UNIT_PIXEL_SIZE);
	mpUnitFactory->init(UNIT_PIXEL_SIZE);
	mpSnake->init(UNIT_PIXEL_SIZE);
	mTargetTimePerFrame = 1000.0f / framesPerSecond;
	mIsRunning = true;
}

void Game::cleanup()
{
	delete mInstance;
	mInstance = nullptr;
}

void Game::doLoop()
{
	Timer timer;
	while (mIsRunning)
	{
		timer.start();
		mpSystem->getInputSystem()->update();
		update(mTargetTimePerFrame);
		render();
		timer.sleepUntilElapsed(mTargetTimePerFrame);
	}
}

void Game::update(float deltaTime)
{
	switch (mGameState)
	{
		case MAIN_MENU: {
			mpMainMenu->update(mTargetTimePerFrame);
			break;
		}
		case MAP_MENU: {
			mpMapMenu->update(mTargetTimePerFrame);
			break;
		}
		case OPTIONS_MENU: {
			mpOptionsMenu->update(mTargetTimePerFrame);
			break;
		}
		case GAMEPLAY: {
			updateGameplay(mTargetTimePerFrame);
			break;
		}
		case ESCAPE_MENU: {
			mpEscapeMenu->update(mTargetTimePerFrame);
			break;
		}
		case RESULT: {
			mpResultScreen->update(mTargetTimePerFrame);
			break;
		}
	}
}

void Game::render()
{
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;
	const string DRAW_TRACKER_NAME = "draw";
	pPerformanceTracker->startTracking(DRAW_TRACKER_NAME);
	switch (mGameState)
	{
		case MAIN_MENU: {
			mpMainMenu->render(mWords[mLanguage]);
			break;
		}
		case MAP_MENU: {
			mpMapMenu->render(mWords[mLanguage]);
			break;
		}
		case OPTIONS_MENU: {
			mpOptionsMenu->render(mWords[mLanguage]);
			break;
		}
		case GAMEPLAY: {
			renderGameplay();
			break;
		}
		case ESCAPE_MENU: {
			mpEscapeMenu->render(mWords[mLanguage]);
			break;
		}
		case RESULT: {
			mpResultScreen->render(mWords[mLanguage]);
			break;
		}
	}
	pPerformanceTracker->stopTracking(DRAW_TRACKER_NAME);
	delete pPerformanceTracker;
}

void Game::updateGameplay(float deltaTime)
{
	// Active Power-Up
	if (mPowerUpActive) {
		mTimeUntilPowerUpReset -= deltaTime;

		if (mTimeUntilPowerUpReset <= 0) {
			resetPowerUps();
		}
	}

	// Power-Up Generation
	mTimeUntilNextPowerUp -= deltaTime;
	if (mTimeUntilNextPowerUp <= 0) {
		mTimeUntilNextPowerUp = TIME_BETWEEN_POWER_UPS;
		addRandomPowerUp();
	}

	// Movement
	mTimeUntilNextMove -= deltaTime;
	if (mTimeUntilNextMove <= 0) {
		mpSnake->update(deltaTime);
		checkCollisions();
		mTimeUntilNextMove = mTimeBetweenMoves;
		mMoveMade = false;
	}

	mpUnitManager->update(deltaTime);
}

void Game::renderGameplay()
{
	mpSystem->getGraphicsSystem()->clear();
	mpSystem->getGraphicsSystem()->draw(Vector2D(0, 0), *mpGraphicsBufferManager->getGraphicsBuffer("Background"));
	mpUnitManager->draw();
	mpSnake->draw();
	mpHud->draw(mWords[mLanguage], mpSnake->getSize() - SNAKE_START_SIZE, mIsGhost, mTimeBetweenMoves != TIME_BETWEEN_MOVES);
	mpSystem->getGraphicsSystem()->flip();
}

void Game::handleEvent(const Event& theEvent)
{
	if (mGameState != GameState::GAMEPLAY) { return; }

	if (theEvent.getType() == MOVE_EVENT) {
		const MoveEvent& gameEvent = static_cast<const MoveEvent&>(theEvent);
		Vector2D snakeDirection = mpSnake->getDirection();
		Vector2D newDirection = gameEvent.getDirection();
		if (!mMoveMade && snakeDirection != newDirection && snakeDirection != newDirection * -1) {
			mpSnake->changeDirection(newDirection);
			mMoveMade = true;
		}
	}
	else if (theEvent.getType() == COLLISION_EVENT) {
		const CollisionEvent& gameEvent = static_cast<const CollisionEvent&>(theEvent);
		Unit* unit = gameEvent.getUnit();
		if (unit != NULL) {
			switch (unit->getType())
			{
			case UnitType::SNAKE:
				if (!mIsGhost) {
					handleSnakeCollision();
				}
				break;
			case UnitType::APPLE:
				handleAppleCollision(unit);
				break;
			case UnitType::ROCK:
				if (!mIsGhost) {
					handleRockCollision();
				}
				break;
			case UnitType::SNAIL:
				handleSnailCollision(unit);
				break;
			case UnitType::GHOST:
				handleGhostCollision(unit);
				break;
			case UnitType::PORTAL:
				handlePortalCollision(unit);
				break;
			}
		}
		else {
			handleWallCollision();
		}
	}
	else if (theEvent.getType() == DISPLAY_ESCAPE_MENU_EVENT) {
		mGameState = GameState::ESCAPE_MENU;
		mpEscapeMenu->renderBackgroundTint();
	}
}

Vector2D Game::getNeighboringPortalLocation(const Vector2D& location)
{
	for (int i = 0; i < mPortals.size(); i++) {
		Vector2D locationOne = mPortals[i].first->getLocation();
		Vector2D locationTwo = mPortals[i].second->getLocation();
		if (Vector2D::getDistanceBetween(locationOne, location) == UNIT_PIXEL_SIZE) {
			return locationOne;
		} else if (Vector2D::getDistanceBetween(locationTwo, location) == UNIT_PIXEL_SIZE) {
			return locationTwo;
		}
	}
	return Vector2D(-1, -1);
}

void Game::save()
{
	// Construct Grid
	int grid[16][16] = { 0 };

	// Units
	for (Unit* unit : mpUnitManager->getUnits()) {
		int x = (int)(unit->getLocation().getX() / UNIT_PIXEL_SIZE);
		int y = (int)(unit->getLocation().getY() / UNIT_PIXEL_SIZE);
		grid[y][x] = unit->getType();
	}

	// Override Portals
	for (int i = 0; i < mPortals.size(); i++) {
		int x1 = (int)(mPortals[i].first->getLocation().getX() / UNIT_PIXEL_SIZE);
		int y1 = (int)(mPortals[i].first->getLocation().getY() / UNIT_PIXEL_SIZE);

		int x2 = (int)(mPortals[i].second->getLocation().getX() / UNIT_PIXEL_SIZE);
		int y2 = (int)(mPortals[i].second->getLocation().getY() / UNIT_PIXEL_SIZE);

		grid[y1][x1] = UnitType::PORTAL + i;
		grid[y2][x2] = UnitType::PORTAL + i;
	}

	// Output Grid
	ofstream foutGrid(SAVED_PATH + SAVED_GRID_FILENAME, ios::out);
	if (foutGrid.is_open()) {
		for (int row = 0; row < ROW_NUM; row++) {
			for (int column = 0; column < COLUMN_NUM; column++) {
				foutGrid << grid[row][column] << ",";
			}
			foutGrid << endl;
		}
		foutGrid.close();
	}

	// Snake
	ofstream foutSnake(SAVED_PATH + SAVED_SNAKE_FILENAME, ios::out);
	if (foutSnake.is_open()) {
		Vector2D snakeDirection = mpSnake->getDirection();
		foutSnake << snakeDirection.getX() << "," << snakeDirection.getY() << endl;

		vector<Unit*> snakeUnits = mpSnake->getUnits();
		for (Unit* unit : snakeUnits) {
			int x = (int)(unit->getLocation().getX() / UNIT_PIXEL_SIZE);
			int y = (int)(unit->getLocation().getY() / UNIT_PIXEL_SIZE);
			foutSnake << x << "," << y << endl;
		}

		foutSnake.close();
	}
}

void Game::load()
{
	reset();

	// Grid
	ifstream finGrid(SAVED_PATH + SAVED_GRID_FILENAME, ios::in);
	if (finGrid.is_open()) {
		unordered_map<int, Vector2D> mapPortalsToLocation;
		string line, value;
		int row = 0;
		while (getline(finGrid, line)) {
			stringstream ss(line);
			int column = 0;
			while (getline(ss, value, ',')) {
				int intValue = stoi(value);
				UnitType type = static_cast<UnitType>(intValue);
				Vector2D currentLocation(column * UNIT_PIXEL_SIZE, row * UNIT_PIXEL_SIZE);
				if (type >= UnitType::PORTAL) {
					if (mapPortalsToLocation.find(intValue) != mapPortalsToLocation.end()) {
						addPortalUnitPair(mapPortalsToLocation[intValue], currentLocation);
					}
					else {
						mapPortalsToLocation[intValue] = currentLocation;
					}
				} else if (type != UnitType::DEFAULT && type != UnitType::EMPTY && type != UnitType::SNAKE) {
					mpUnitManager->addUnit(mpUnitFactory->createUnit(type, currentLocation));
				}
				column++;
			}
			row++;
		}
		finGrid.close();
	}

	// Snake
	ifstream finSnake(SAVED_PATH + SAVED_SNAKE_FILENAME, ios::in);
	if (finSnake.is_open()) {
		string line, valueX, valueY;

		// Direction
		getline(finSnake, line);
		stringstream ss(line);
		getline(ss, valueX, ',');
		getline(ss, valueY, ',');
		mpSnake->changeDirection(Vector2D(stoi(valueX), stoi(valueY)));

		// Positions
		while (getline(finSnake, line)) {
			stringstream ss(line);
			getline(ss, valueX, ',');
			getline(ss, valueY, ',');
			mpSnake->grow(mpUnitFactory->createUnit(UnitType::SNAKE, Vector2D(stoi(valueX) * UNIT_PIXEL_SIZE, stoi(valueY) * UNIT_PIXEL_SIZE)));
		}

		finSnake.close();
	}

	mpSnake->updateAnimations();
}

void Game::loadMap(const string& filename)
{
	reset();

	ifstream fin(MAP_PATH + filename, ios::in);
	if (fin.is_open()) {
		unordered_map<int, Vector2D> mapPortalsToLocation;
		string line, value;
		int row = 0;
		while (getline(fin, line)) {
			stringstream ss(line);
			int column = 0;
			while (getline(ss, value, ',')) {
				int intValue = stoi(value);
				UnitType item = static_cast<UnitType>(intValue);
				Vector2D currentLocation(column * UNIT_PIXEL_SIZE, row * UNIT_PIXEL_SIZE);

				if (item == UnitType::ROCK) {
					mpUnitManager->addUnit(mpUnitFactory->createUnit(UnitType::ROCK, currentLocation));
				}
				else if (item >= UnitType::PORTAL) {
					if (mapPortalsToLocation.find(intValue) != mapPortalsToLocation.end()) {
						addPortalUnitPair(mapPortalsToLocation[intValue], currentLocation);
					}
					else {
						mapPortalsToLocation[intValue] = currentLocation;
					}
				}
				column++;
			}
			row++;
		}
		fin.close();
	}
	startGame();
}

void Game::playAgain()
{
	resetPowerUps();
	mTimeUntilNextPowerUp = TIME_BETWEEN_POWER_UPS;
	mpSnake->clear();
	mpUnitManager->removeNonMapUnits();
	startGame();
}

Game::Game()
{
	mpSystem = new System;
	mpInputTranslator = new InputTranslator;
	mpUnitManager = new UnitManager;
	mpGraphicsBufferManager = new GraphicsBufferManager;
	mpUnitFactory = new UnitFactory;
	mpMainMenu = new MainMenu;
	mpMapMenu = new MapMenu;
	mpOptionsMenu = new OptionsMenu;
	mpEscapeMenu = new EscapeMenu;
	mpHud = new Hud;
	mpResultScreen = new ResultScreen;
	mpSoundSystem = new SoundSystem;
	mpSnake = new Snake;
}

Game::~Game()
{
	EventSystem::getInstance()->removeListener((EventType)MOVE_EVENT, this);
	EventSystem::getInstance()->removeListener((EventType)COLLISION_EVENT, this);
	EventSystem::getInstance()->removeListener((EventType)DISPLAY_ESCAPE_MENU_EVENT, this);
	delete mpSoundSystem;
	delete mpResultScreen;
	delete mpHud;
	delete mpMainMenu;
	delete mpMapMenu;
	delete mpOptionsMenu;
	delete mpEscapeMenu;
	delete mpInputTranslator;
	delete mpUnitManager;
	delete mpGraphicsBufferManager;
	delete mpUnitFactory;
	delete mpSnake;
	delete mpSystem;
	mIsRunning = false;
}

void Game::loadWords()
{
	ifstream fin(ASSET_PATH + WORDS_FILENAME, ios::in);
	if (fin.is_open()) {
		string line, value;
		getline(fin, line); // Ignore Headers
		while (getline(fin, line)) {
			stringstream ss(line);
			Language language = Language::ENGLISH;
			string key;
			while (getline(ss, value, ',')) {
				if (language == Language::ENGLISH) {
					key = value;
				}
				mWords[language][key] = value;
				language = static_cast<Language>(static_cast<int>(language) + 1);
			}
		}
		fin.close();
	}
}

void Game::startGame()
{
	mpSnake->grow(mpUnitFactory->createUnit(UnitType::SNAKE, mSnakeStartLocation));
	for (int i = 0; i < SNAKE_START_SIZE - 1; i++) {
		mpSnake->grow(mpUnitFactory->createUnit(UnitType::SNAKE, mpSnake->getBehindTailLocation()));
	}
	mpUnitManager->addUnit(mpUnitFactory->createUnit(UnitType::APPLE, generateRandomOpenLocation()));
	mpSnake->changeDirection(Vector2D(1, 0));
	mpSnake->updateAnimations();
}

void Game::reset()
{
	resetPowerUps();
	mTimeUntilNextPowerUp = TIME_BETWEEN_POWER_UPS;
	mpSnake->clear();
	mpUnitManager->clear();
	mPortals.clear();
	mpUnitFactory->resetPortalCount();
}

void Game::addPortalUnitPair(const Vector2D& locationOne, const Vector2D& locationTwo)
{
	Unit* portalOne = mpUnitFactory->createUnit(UnitType::PORTAL, locationOne);
	Unit* portalTwo = mpUnitFactory->createUnit(UnitType::PORTAL, locationTwo);
	mpUnitManager->addUnit(portalOne);
	mpUnitManager->addUnit(portalTwo);
	mPortals.push_back(make_pair(portalOne, portalTwo));
}

void Game::addRandomPowerUp()
{
	UnitType type;
	if (rand() % 2 == 0) {
		type = UnitType::SNAIL;
	}
	else {
		type = UnitType::GHOST;
	}
	mpUnitManager->addUnit(mpUnitFactory->createUnit(type, generateRandomOpenLocation()));
}

void Game::resetPowerUps()
{
	mTimeBetweenMoves = TIME_BETWEEN_MOVES;
	mIsGhost = false;

	mTimeUntilPowerUpReset = TIME_POWER_UP_LAST;
	mPowerUpActive = false;
}

Vector2D Game::generateRandomOpenLocation()
{
	while (true) {
		Vector2D randLocation((rand() % COLUMN_NUM) * UNIT_PIXEL_SIZE, (rand() % ROW_NUM) * UNIT_PIXEL_SIZE);
		if (!mpUnitManager->occupyingLocation(randLocation) && !mpSnake->occupyingLocation(randLocation)) {
			return randLocation;
		}
	}
}

void Game::checkCollisions()
{
	// Units
	for (Unit* unit : mpUnitManager->getUnits()) {
		if (mpSnake->getHeadLocation() == unit->getLocation()) {
			CollisionEvent event(unit);
			EventSystem::getInstance()->fireEvent(event);
		}
	}

	// Snake
	for (int i = 1; i < mpSnake->getSize(); i++) {
		if (mpSnake->getSnakeUnitLocation(i) == mpSnake->getHeadLocation()) {
			CollisionEvent event(mpSnake->getUnit(i));
			EventSystem::getInstance()->fireEvent(event);
		}
	}

	// Wall
	if (mpSnake->getHeadLocation().getX() > UNIT_PIXEL_SIZE * (COLUMN_NUM - 1) ||
		mpSnake->getHeadLocation().getX() < 0 ||
		mpSnake->getHeadLocation().getY() > UNIT_PIXEL_SIZE * (ROW_NUM - 1) ||
		mpSnake->getHeadLocation().getY() < 0)
	{
		CollisionEvent event(NULL);
		EventSystem::getInstance()->fireEvent(event);
	}
}

void Game::handlePortalCollision(Unit* portal)
{
	mpSoundSystem->playSound("Portal Effect", false);
	for (auto& it : mPortals) {
		if (it.first == portal) {
			mpSnake->getHead()->setLocation(it.second->getLocation() + mpSnake->getDirection() * UNIT_PIXEL_SIZE);
			return;
		}
		else if (it.second == portal) {
			mpSnake->getHead()->setLocation(it.first->getLocation() + mpSnake->getDirection() * UNIT_PIXEL_SIZE);
			return;
		}
	}
}

void Game::handleSnailCollision(Unit* snail)
{
	mpSoundSystem->playSound("Power-Up Effect", false);
	mpUnitManager->removeUnit(snail);
	resetPowerUps();
	mTimeBetweenMoves = TIME_BETWEEN_MOVES / mPowerUpSpeedPercentage;
	mPowerUpActive = true;
}

void Game::handleGhostCollision(Unit* ghost)
{
	mpSoundSystem->playSound("Power-Up Effect", false);
	mpUnitManager->removeUnit(ghost);
	resetPowerUps();
	mIsGhost = true;
	mPowerUpActive = true;
}

void Game::handleRockCollision()
{
	mpSoundSystem->playSound("Lose Effect", false);
	mpResultScreen->setResult(mpSnake->getSize() - SNAKE_START_SIZE);
	mGameState = GameState::RESULT;
}

void Game::handleAppleCollision(Unit* apple)
{
	mpSoundSystem->playSound("Apple Effect", false);
	mpSnake->grow(mpUnitFactory->createUnit(UnitType::SNAKE, mpSnake->getBehindTailLocation()));
	mpSnake->updateAnimations();

	if (mpSnake->getSize() < (ROW_NUM * COLUMN_NUM) - mpUnitManager->getMapUnitCount()) {
		apple->setLocation(generateRandomOpenLocation());
	}
	else { // no spaces left
		mpResultScreen->setResult(mpSnake->getSize() - SNAKE_START_SIZE);
		mGameState = GameState::RESULT;
	}
}

void Game::handleSnakeCollision()
{
	mpSoundSystem->playSound("Lose Effect", false);
	mpResultScreen->setResult(mpSnake->getSize() - SNAKE_START_SIZE);
	mGameState = GameState::RESULT;
}

void Game::handleWallCollision()
{
	mpSoundSystem->playSound("Lose Effect", false);
	mpResultScreen->setResult(mpSnake->getSize() - SNAKE_START_SIZE);
	mGameState = GameState::RESULT;
}