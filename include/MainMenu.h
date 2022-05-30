#pragma once
#include "Menu.h"

class MainMenu : public Menu
{
public:
	MainMenu() {};
	void init();
	void render(std::unordered_map<std::string, std::string>& words);
	void handleEvent(const Event& theEvent);
private:
	const std::string mTextKeys[4] = { "Play", "Load", "Options", "Exit" };
	const std::string MAIN_MENU = "main-menu.png";
	const int BUTTON_ALIGN_X = (CANVAS_WIDTH - BUTTON_WIDTH) / 2;
	const int BUTTON_ALIGN_Y = 362;
	const int BUTTON_OFFSET_Y = 100;
};
