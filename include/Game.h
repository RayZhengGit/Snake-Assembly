#pragma once

#include <System.h>
#include "UnitManager.h"
#include "GraphicsBufferManager.h"
#include "UnitFactory.h"
#include "Unit.h"
#include <GraphicsBuffer.h>
#include <string>
#include <EventListener.h>
#include <Event.h>
#include "InputTranslator.h"
#include "Snake.h"
#include "Hud.h"
#include "SoundSystem.h"

class UnitFactory;
class MainMenu;
class MapMenu;
class OptionsMenu;
class EscapeMenu;
class Hud;
class ResultScreen;

enum GameState {
	MAIN_MENU,
	MAP_MENU,
	OPTIONS_MENU,
	GAMEPLAY,
	ESCAPE_MENU,
	RESULT
};

enum Language {
	ENGLISH,
	FRENCH,
	SPANISH
};

class Game : public EventListener
{
public:
	Game(const Game&) = delete;
	static Game* getInstance();
	void init(unsigned int width, unsigned int height, unsigned int framesPerSecond);
	void cleanup();
	void doLoop();
	void update(float deltaTime);
	void render();
	void updateGameplay(float deltaTime);
	void renderGameplay();
	void handleEvent(const Event& theEvent);

	System* getSystem() const { return mpSystem; };
	GraphicsBufferManager* getGraphicsBufferManager() const { return mpGraphicsBufferManager; };
	SoundSystem* getSoundSystem() const { return mpSoundSystem; };
	void setIsRunning(bool isRunning) { mIsRunning = isRunning; };
	GameState getGameState() const { return mGameState; };
	void setGameState(GameState gameState) { mGameState = gameState; };
	void setLanguage(Language language) { mLanguage = language; };
	Vector2D getNeighboringPortalLocation(const Vector2D& location);
	void save();
	void load();
	void loadMap(const string& filename);
	void playAgain();

private:
	static Game* mInstance;
	Game();
	~Game();
	GameState mGameState = GameState::MAIN_MENU;
	System* mpSystem = NULL;
	SoundSystem* mpSoundSystem = NULL;
	InputTranslator* mpInputTranslator = NULL;
	UnitManager* mpUnitManager = NULL;
	GraphicsBufferManager* mpGraphicsBufferManager = NULL;
	UnitFactory* mpUnitFactory = NULL;
	MainMenu* mpMainMenu = NULL;
	MapMenu* mpMapMenu = NULL;
	OptionsMenu* mpOptionsMenu = NULL;
	EscapeMenu* mpEscapeMenu = NULL;
	Hud* mpHud = NULL;
	ResultScreen* mpResultScreen = NULL;
	float mTargetTimePerFrame;
	bool mIsRunning = false;

	const int ROW_NUM = 16;
	const int COLUMN_NUM = 16;
	const int UNIT_PIXEL_SIZE = 64;

	const float TIME_BETWEEN_MOVES = 125; // constant to reset value
	float mTimeBetweenMoves = TIME_BETWEEN_MOVES;
	float mTimeUntilNextMove = TIME_BETWEEN_MOVES;
	bool mMoveMade = false;

	const float TIME_POWER_UP_LAST = 10 * 1000;
	float mTimeUntilPowerUpReset = TIME_POWER_UP_LAST;
	bool mPowerUpActive = false;

	const string ASSET_PATH = "assets/";
	const string GAMEPLAY_BACKGROUND_FILENAME = "gameplay-background.png";
	const string SNAKE_GRAPHICS_FILENAME = "snake-graphics.png";
	const string PURPLE_PORTAL_FILENAME = "portal-purple.png";
	const string BLUE_PORTAL_FILENAME = "portal-blue.png";
	const string RED_PORTAL_FILENAME = "portal-red.png";
	const string SNAIL_FILENAME = "snail.png";
	const string GHOST_FILENAME = "ghost.png";
	const string ROCK_FILENAME = "rock.png";

	const string SAVED_PATH = "saved/";
	const string SAVED_GRID_FILENAME = "saved-grid.csv";
	const string SAVED_SNAKE_FILENAME = "saved-snake.csv";

	const string MAP_PATH = "maps/";
	const string DEFAULT_MAP_FILENAME = "default.csv";
	const string ROCK_MAP_FILENAME = "rocks.csv";
	const string PORTAL_MAP_FILENAME = "portals.csv";
	const string ROCK_AND_PORTAL_MAP_FILENAME = "rocks-and-portals.csv";

	const string WORDS_FILENAME = "word-translations.csv";
	Language mLanguage = Language::ENGLISH;
	unordered_map<Language, unordered_map<string, string>> mWords; // Ex. mWords[FRENCH]["Play"] = "Jouer"
	void loadWords();

	Vector2D mSnakeStartLocation = Vector2D(5 * UNIT_PIXEL_SIZE, 8 * UNIT_PIXEL_SIZE);
	const int SNAKE_START_SIZE = 3;
	void startGame();
	void reset();

	Snake* mpSnake = NULL;
	vector<pair<Unit*, Unit*>> mPortals;
	void addPortalUnitPair(const Vector2D& locationOne, const Vector2D& locationTwo);

	const float TIME_BETWEEN_POWER_UPS = 15 * 1000;
	float mTimeUntilNextPowerUp = TIME_BETWEEN_POWER_UPS;
	const float mPowerUpSpeedPercentage = 0.5;
	bool mIsGhost = false;
	void addRandomPowerUp();
	void resetPowerUps();
	Vector2D generateRandomOpenLocation();

	void checkCollisions();
	void handlePortalCollision(Unit* portal);
	void handleSnailCollision(Unit* snail);
	void handleGhostCollision(Unit* ghost);
	void handleRockCollision();
	void handleAppleCollision(Unit* apple);
	void handleSnakeCollision();
	void handleWallCollision();
};