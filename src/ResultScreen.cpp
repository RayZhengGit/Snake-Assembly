#include "ResultScreen.h"
#include "Game.h"
#include "GameEvents.h"

ResultScreen::~ResultScreen()
{
	Menu::~Menu();
	delete mpResultFont;
	delete mpSmallFont;
}

void ResultScreen::init()
{
	Menu::init();
	mpResultFont = new Font(ASSET_PATH + FONT, RESULT_FONT_SIZE);
	mpSmallFont = new Font(ASSET_PATH + FONT, SMALL_FONT_SIZE);

	// Add Buttons
	addButtonUnit(Vector2D(BUTTON_ALIGN_X, BUTTON_ALIGN_Y + BUTTON_OFFSET_Y * 1)); // Play Again
	addButtonUnit(Vector2D(BUTTON_ALIGN_X, BUTTON_ALIGN_Y + BUTTON_OFFSET_Y * 2)); // Leave
}

void ResultScreen::render(std::unordered_map<std::string, std::string>& words)
{
	mpSystem->getGraphicsSystem()->clear();
	mpSystem->getGraphicsSystem()->draw(Vector2D(0, 0), *mpGraphicsBufferManager->getGraphicsBuffer("Logoless Menu"));
	mpSystem->getGraphicsSystem()->writeText(Vector2D(BUTTON_ALIGN_X, CANVAS_HEIGHT / 4) + Vector2D(BUTTON_WIDTH / 2, BUTTON_HEIGHT / 4), *mpResultFont, Color(0, 0, 0), words[mTextKeys[0]] + ": " + to_string(mResult), Font::CENTER);
	for (int i = 0; i < mButtons.size(); i++) {
		mButtons[i]->draw();
		mpSystem->getGraphicsSystem()->writeText(mButtons[i]->getLocation() + Vector2D(BUTTON_WIDTH / 2, BUTTON_HEIGHT / 4), *mpSmallFont, Color(0, 0, 0), words[mTextKeys[i + 1]], Font::CENTER);
	}
	mpSystem->getGraphicsSystem()->flip();
}

void ResultScreen::handleEvent(const Event& theEvent)
{
	if (Game::getInstance()->getGameState() != GameState::RESULT) { return; }

	if (theEvent.getType() == CLICK_EVENT) {
		const ClickEvent& gameEvent = static_cast<const ClickEvent&>(theEvent);
		for (int i = 0; i < mButtons.size(); i++) {
			if (mButtons[i]->isClicked(gameEvent.getPosition())) {
				mpSoundSystem->playSound("Button Click", false);
				switch (i)
				{
					case 0: // Play Again
						Game::getInstance()->playAgain();
						Game::getInstance()->setGameState(GameState::GAMEPLAY);
						break;
					case 1: // Leave
						Game::getInstance()->setGameState(GameState::MAIN_MENU);
						break;
				}
			}
		}
	}
}
