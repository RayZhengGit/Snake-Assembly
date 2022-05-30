#pragma once
#include "Menu.h"

class OptionsMenu : public Menu
{
public:
	OptionsMenu() {};
	~OptionsMenu();
	void init();
	void render(std::unordered_map<std::string, std::string>& words);
	void handleEvent(const Event& theEvent);
private:
	const std::string mTextKeys[5] = { "Sound", "Effects", "Music", "Language", "Back" };
	const std::string mLanguagesText[3] = { "English", "Francais", "Espanol" }; // not translated

	Font* mpHeaderFont = NULL;
	const int HEADER_FONT_SIZE = 72;
	const std::string GREEN_TOGGLE = "green-toggle.png";
	const std::string GREY_TOGGLE = "grey-toggle.png";

	const int START_Y = 150;
	const int SPACING_X = 40;
	const int SPACING_Y = 110;
	const int TOGGLE_ALIGN_X = CANVAS_WIDTH / 2 + SPACING_X;
	const int SOUND_TEXT_ALIGN_X = CANVAS_WIDTH / 2 - SPACING_X;
	const int CATEGORY_SPACING_Y = 150;
	const int BUTTON_ALIGN_X = (CANVAS_WIDTH - BUTTON_WIDTH) / 2;
	const int BACK_BUTTON_ALIGN_Y = 855;
};
