#include "EscapeMenu.h"
#include "Game.h"
#include "GameEvents.h"

void EscapeMenu::init()
{
	Menu::init();
	mpGraphicsBufferManager->addGraphicsBuffer("Grey Background", new GraphicsBuffer(ASSET_PATH + BACKGROUND));

	// Add Buttons
	addButtonUnit(Vector2D((CANVAS_WIDTH - BUTTON_WIDTH) / 2, (CANVAS_HEIGHT - BUTTON_HEIGHT) / 2 - BUTTON_OFFSET_Y)); // Resume
	addButtonUnit(Vector2D((CANVAS_WIDTH - BUTTON_WIDTH) / 2, (CANVAS_HEIGHT - BUTTON_HEIGHT) / 2)); // Save
	addButtonUnit(Vector2D((CANVAS_WIDTH - BUTTON_WIDTH) / 2, (CANVAS_HEIGHT - BUTTON_HEIGHT) / 2 + BUTTON_OFFSET_Y)); // Leave
}

void EscapeMenu::render(std::unordered_map<std::string, std::string>& words)
{
	for (int i = 0; i < mButtons.size(); i++) {
		mButtons[i]->draw();
		mpSystem->getGraphicsSystem()->writeText(mButtons[i]->getLocation() + Vector2D(BUTTON_WIDTH / 2, BUTTON_HEIGHT / 4), *mpFont, Color(0, 0, 0), words[mTextKeys[i]], Font::CENTER);
	}
	mpSystem->getGraphicsSystem()->flip();
}

void EscapeMenu::handleEvent(const Event& theEvent)
{
	if (Game::getInstance()->getGameState() != GameState::ESCAPE_MENU) { return; }

	if (theEvent.getType() == CLICK_EVENT) {
		const ClickEvent& gameEvent = static_cast<const ClickEvent&>(theEvent);
		for (int i = 0; i < mButtons.size(); i++) {
			if (mButtons[i]->isClicked(gameEvent.getPosition())) {
				mpSoundSystem->playSound("Button Click", false);
				switch (i)
				{
					case 0: // Resume
						Game::getInstance()->setGameState(GameState::GAMEPLAY);
						break;
					case 1: // Save
						Game::getInstance()->setGameState(GameState::MAIN_MENU);
						Game::getInstance()->save();
						break;
					case 2: // Leave
						Game::getInstance()->setGameState(GameState::MAIN_MENU);
						break;
				}
			}
		}
	}
}

void EscapeMenu::renderBackgroundTint() {
	mpSystem->getGraphicsSystem()->addTint(*mpGraphicsBufferManager->getGraphicsBuffer("Grey Background"));
}
