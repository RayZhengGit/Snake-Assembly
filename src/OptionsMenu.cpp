#include "OptionsMenu.h"
#include "Game.h"
#include "GameEvents.h"

OptionsMenu::~OptionsMenu()
{
	Menu::~Menu();
	delete mpHeaderFont;
}

void OptionsMenu::init()
{
	Menu::init();
	mpHeaderFont = new Font(ASSET_PATH + FONT, HEADER_FONT_SIZE);

	mpGraphicsBufferManager->addGraphicsBuffer("Green Toggle", new GraphicsBuffer(ASSET_PATH + GREEN_TOGGLE));
	mpGraphicsBufferManager->addGraphicsBuffer("Grey Toggle", new GraphicsBuffer(ASSET_PATH + GREY_TOGGLE));

	// Add Buttons
	addToggleUnit(Vector2D(TOGGLE_ALIGN_X, START_Y + SPACING_Y)); // Sound Effects
	addToggleUnit(Vector2D(TOGGLE_ALIGN_X, START_Y + 2 * SPACING_Y)); // Music
	addButtonUnit(Vector2D(BUTTON_ALIGN_X - BUTTON_WIDTH - SPACING_X, START_Y + CATEGORY_SPACING_Y + 3 * SPACING_Y)); // English
	addButtonUnit(Vector2D(BUTTON_ALIGN_X, START_Y + CATEGORY_SPACING_Y + 3 * SPACING_Y)); // French
	addButtonUnit(Vector2D(BUTTON_ALIGN_X + BUTTON_WIDTH + SPACING_X, START_Y + CATEGORY_SPACING_Y + 3 * SPACING_Y)); // Spanish
	addButtonUnit(Vector2D(BUTTON_ALIGN_X, BACK_BUTTON_ALIGN_Y)); // Back
}

void OptionsMenu::render(std::unordered_map<std::string, std::string>& words)
{
	mpSystem->getGraphicsSystem()->clear();
	mpSystem->getGraphicsSystem()->draw(Vector2D(0, 0), *mpGraphicsBufferManager->getGraphicsBuffer("Logoless Menu"));

	mpSystem->getGraphicsSystem()->writeText(Vector2D(CANVAS_WIDTH / 2, START_Y), *mpHeaderFont, Color(0, 0, 0), words[mTextKeys[0]], Font::CENTER);
	mpSystem->getGraphicsSystem()->writeText(Vector2D(SOUND_TEXT_ALIGN_X, START_Y + SPACING_Y + 15), *mpFont, Color(0, 0, 0), words[mTextKeys[1]], Font::RIGHT);
	mpSystem->getGraphicsSystem()->writeText(Vector2D(SOUND_TEXT_ALIGN_X, START_Y + 2 * SPACING_Y + 15), *mpFont, Color(0, 0, 0), words[mTextKeys[2]], Font::RIGHT);
	mpSystem->getGraphicsSystem()->writeText(Vector2D(CANVAS_WIDTH / 2, START_Y + CATEGORY_SPACING_Y + 2 * SPACING_Y), *mpHeaderFont, Color(0, 0, 0), words[mTextKeys[3]], Font::CENTER);

	for (int i = 0; i < mButtons.size(); i++) {
		mButtons[i]->draw();

		std::string text;
		if (i == 5) { // Back Button
			text = words[mTextKeys[i - 1]];
		} 
		else if (i >= 2) { // Language Buttons
			text = mLanguagesText[i - 2];
		}
		mpSystem->getGraphicsSystem()->writeText(mButtons[i]->getLocation() + Vector2D(BUTTON_WIDTH / 2, BUTTON_HEIGHT / 4), *mpFont, Color(0, 0, 0), text, Font::CENTER);
	}
	mpSystem->getGraphicsSystem()->flip();
}

void OptionsMenu::handleEvent(const Event& theEvent)
{
	if (Game::getInstance()->getGameState() != GameState::OPTIONS_MENU) { return; }

	if (theEvent.getType() == CLICK_EVENT) {
		const ClickEvent& gameEvent = static_cast<const ClickEvent&>(theEvent);
		for (int i = 0; i < mButtons.size(); i++) {
			if (mButtons[i]->isClicked(gameEvent.getPosition())) {
				mpSoundSystem->playSound("Button Click", false);
				switch (i)
				{
					case 0: // Toggle Sound Effects
						if (mButtons[i]->getCurrentAnimationKey() == "Toggle - On") {
							mButtons[i]->setCurrentAnimation("Toggle - Off");
							mpSoundSystem->disableEffects();
						}
						else {
							mButtons[i]->setCurrentAnimation("Toggle - On");
							mpSoundSystem->enableEffects();
						}
						break;
					case 1: // Toggle Music
						if (mButtons[i]->getCurrentAnimationKey() == "Toggle - On") {
							mButtons[i]->setCurrentAnimation("Toggle - Off");
							mpSoundSystem->stopMusic();
							mpSoundSystem->playSound("Button Click", false);
						}
						else {
							mButtons[i]->setCurrentAnimation("Toggle - On");
							mpSoundSystem->startMusic();
						}
						break;
					case 2: // English Button
						Game::getInstance()->setLanguage(Language::ENGLISH);
						break;
					case 3: // French Button
						Game::getInstance()->setLanguage(Language::FRENCH);
						break;
					case 4: // Spanish Button
						Game::getInstance()->setLanguage(Language::SPANISH);
						break;
					case 5: // Back Button
						Game::getInstance()->setGameState(GameState::MAIN_MENU);
						break;
				}
			}
		}
	}
}
