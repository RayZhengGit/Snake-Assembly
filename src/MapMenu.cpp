#include "MapMenu.h"
#include "Game.h"
#include "GameEvents.h"

void MapMenu::init()
{
	Menu::init();
	mpGraphicsBufferManager->addGraphicsBuffer("Button", new GraphicsBuffer(ASSET_PATH + BUTTON));

	mpGraphicsBufferManager->addGraphicsBuffer("Logoless Menu", new GraphicsBuffer(ASSET_PATH + BACKGROUND));
	mpGraphicsBufferManager->addGraphicsBuffer("Default Map", new GraphicsBuffer(ASSET_PATH + DEFAULT_MAP_PREVIEW));
	mpGraphicsBufferManager->addGraphicsBuffer("Rock Map", new GraphicsBuffer(ASSET_PATH + ROCK_MAP_PREVIEW));
	mpGraphicsBufferManager->addGraphicsBuffer("Portal Map", new GraphicsBuffer(ASSET_PATH + PORTAL_MAP_PREVIEW));
	mpGraphicsBufferManager->addGraphicsBuffer("Rock and Portal Map", new GraphicsBuffer(ASSET_PATH + ROCK_AND_PORTAL_MAP_PREVIEW));

	// Default Map Button
	Animation* defaultMapAnimation = new Animation(180.0f, true);
	defaultMapAnimation->addSprite({ mpGraphicsBufferManager->getGraphicsBuffer("Default Map"), Vector2D(0, 0), MAP_PREVIEW_WIDTH, MAP_PREVIEW_HEIGHT });

	Unit* defaultMapUnit = new Unit(Vector2D(IMG_ALIGN_X, IMG_ALIGN_Y));
	defaultMapUnit->addAnimation("Default Map", defaultMapAnimation);
	mButtons.push_back(defaultMapUnit);

	// Rock Map Button
	Animation* rockMapAnimation = new Animation(180.0f, true);
	rockMapAnimation->addSprite({ mpGraphicsBufferManager->getGraphicsBuffer("Rock Map"), Vector2D(0, 0), MAP_PREVIEW_WIDTH, MAP_PREVIEW_HEIGHT });

	Unit* rockMapUnit = new Unit(Vector2D(IMG_ALIGN_X + CANVAS_WIDTH / 3, IMG_ALIGN_Y));
	rockMapUnit->addAnimation("Rock Map", rockMapAnimation);
	mButtons.push_back(rockMapUnit);

	// Portal Map Button
	Animation* portalMapAnimation = new Animation(180.0f, true);
	portalMapAnimation->addSprite({ mpGraphicsBufferManager->getGraphicsBuffer("Portal Map"), Vector2D(0, 0), MAP_PREVIEW_WIDTH, MAP_PREVIEW_HEIGHT });

	Unit* portalMapUnit = new Unit(Vector2D(IMG_ALIGN_X, IMG_ALIGN_Y + CANVAS_HEIGHT / 3));
	portalMapUnit->addAnimation("Portal Map", portalMapAnimation);
	mButtons.push_back(portalMapUnit);

	// Rock and Portal Map Button
	Animation* rockPortalMapAnimation = new Animation(180.0f, true);
	rockPortalMapAnimation->addSprite({ mpGraphicsBufferManager->getGraphicsBuffer("Rock and Portal Map"), Vector2D(0, 0), MAP_PREVIEW_WIDTH, MAP_PREVIEW_HEIGHT });

	Unit* rockPortalMapUnit = new Unit(Vector2D(IMG_ALIGN_X + CANVAS_WIDTH / 3, IMG_ALIGN_Y + CANVAS_HEIGHT / 3));
	rockPortalMapUnit->addAnimation("Rock and Portal Map", rockPortalMapAnimation);
	mButtons.push_back(rockPortalMapUnit);

	// Back Button
	addButtonUnit(Vector2D(BUTTON_ALIGN_X, BUTTON_ALIGN_Y));
}

void MapMenu::render(std::unordered_map<std::string, std::string>& words)
{
	mpSystem->getGraphicsSystem()->clear();
	mpSystem->getGraphicsSystem()->draw(Vector2D(0, 0), *mpGraphicsBufferManager->getGraphicsBuffer("Logoless Menu"));
	for (int i = 0; i < mButtons.size(); i++) {
		mButtons[i]->draw();
		if (i == 4) {
			mpSystem->getGraphicsSystem()->writeText(mButtons[i]->getLocation() + Vector2D(BUTTON_WIDTH / 2, BUTTON_HEIGHT / 4), *mpFont, Color(0, 0, 0), words[mTextKeys[i]], Font::CENTER);
		} else {
			mpSystem->getGraphicsSystem()->writeText(mButtons[i]->getLocation() + Vector2D(MAP_PREVIEW_WIDTH / 2, MAP_PREVIEW_HEIGHT), *mpFont, Color(0, 0, 0), words[mTextKeys[i]], Font::CENTER);
		}
	}
	mpSystem->getGraphicsSystem()->flip();
}

void MapMenu::handleEvent(const Event& theEvent)
{
	if (Game::getInstance()->getGameState() != GameState::MAP_MENU) { return; }

	if (theEvent.getType() == CLICK_EVENT) {
		const ClickEvent& gameEvent = static_cast<const ClickEvent&>(theEvent);
		for (int i = 0; i < mButtons.size(); i++) {
			if (mButtons[i]->isClicked(gameEvent.getPosition())) {
				mpSoundSystem->playSound("Button Click", false);
				if (i == 4) { // Back Button
					Game::getInstance()->setGameState(GameState::MAIN_MENU);
				}
				else { // Map Button
					switch (i)
					{
						case 0: // Default
							Game::getInstance()->loadMap(DEFAULT_MAP_FILENAME);
							break;
						case 1: // Rock
							Game::getInstance()->loadMap(ROCK_MAP_FILENAME);
							break;
						case 2: // Portal
							Game::getInstance()->loadMap(PORTAL_MAP_FILENAME);
							break;
						case 3: // Both
							Game::getInstance()->loadMap(ROCK_AND_PORTAL_MAP_FILENAME);
							break;
					}
					Game::getInstance()->setGameState(GameState::GAMEPLAY);
				}
			}
		}
	}
}
