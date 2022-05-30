#include "MainMenu.h"
#include "Game.h"
#include "GameEvents.h"

void MainMenu::init()
{
	Menu::init();
	mpGraphicsBufferManager->addGraphicsBuffer("Main Menu", new GraphicsBuffer(ASSET_PATH + MAIN_MENU));

	// Add Buttons
	addButtonUnit(Vector2D(BUTTON_ALIGN_X, BUTTON_ALIGN_Y + BUTTON_OFFSET_Y)); // Play
	addButtonUnit(Vector2D(BUTTON_ALIGN_X, BUTTON_ALIGN_Y + BUTTON_OFFSET_Y * 2)); // Load
	addButtonUnit(Vector2D(BUTTON_ALIGN_X, BUTTON_ALIGN_Y + BUTTON_OFFSET_Y * 3)); // Options
	addButtonUnit(Vector2D(BUTTON_ALIGN_X, BUTTON_ALIGN_Y + BUTTON_OFFSET_Y * 4)); // Exit
}

void MainMenu::render(std::unordered_map<std::string, std::string>& words)
{
	mpSystem->getGraphicsSystem()->clear();
	mpSystem->getGraphicsSystem()->draw(Vector2D(0, 0), *mpGraphicsBufferManager->getGraphicsBuffer("Main Menu"));
	for (int i = 0; i < mButtons.size(); i++) {
		mButtons[i]->draw();
		mpSystem->getGraphicsSystem()->writeText(mButtons[i]->getLocation() + Vector2D(BUTTON_WIDTH / 2, BUTTON_HEIGHT / 4), *mpFont, Color(0, 0, 0), words[mTextKeys[i]], Font::CENTER);
	}
	mpSystem->getGraphicsSystem()->flip();
}

void MainMenu::handleEvent(const Event& theEvent)
{
	if (Game::getInstance()->getGameState() != GameState::MAIN_MENU) { return; }

	if (theEvent.getType() == CLICK_EVENT) {
		const ClickEvent& gameEvent = static_cast<const ClickEvent&>(theEvent);
		for (int i = 0; i < mButtons.size(); i++) {
			if (mButtons[i]->isClicked(gameEvent.getPosition())) {
				mpSoundSystem->playSound("Button Click", false);
				switch (i)
				{
					case 0: // Play
						Game::getInstance()->setGameState(GameState::MAP_MENU);
						break;
					case 1: // Load
						Game::getInstance()->load();
						Game::getInstance()->setGameState(GameState::GAMEPLAY);
						break;
					case 2: // Options
						Game::getInstance()->setGameState(GameState::OPTIONS_MENU);
						break;
					case 3: // Exit
						Game::getInstance()->setIsRunning(false);
						break;
				}
			}
		}
	}
}
