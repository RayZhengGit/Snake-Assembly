#pragma once
#include "Menu.h"

class EscapeMenu: public Menu
{
public:
	EscapeMenu() {};
	void init();
	void render(std::unordered_map<std::string, std::string>& words);
	void handleEvent(const Event& theEvent);
	void renderBackgroundTint();
private:
	const std::string mTextKeys[3] = { "Resume", "Save", "Leave" };
	const std::string BACKGROUND = "grey-background.png";
	const int BUTTON_OFFSET_Y = 100;
};
