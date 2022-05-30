#pragma once
#include "Menu.h"

class ResultScreen : public Menu
{
public:
	ResultScreen() {};
	~ResultScreen();
	void init();
	void render(std::unordered_map<std::string, std::string>& words);
	void handleEvent(const Event& theEvent);
	void setResult(int result) { mResult = result; };
private:
	const std::string mTextKeys[3] = { "Score", "Play Again", "Leave" };
	Font* mpResultFont = NULL;
	Font* mpSmallFont = NULL;
	const int BUTTON_ALIGN_X = CANVAS_WIDTH / 2 - BUTTON_WIDTH / 2;
	const int BUTTON_ALIGN_Y = 362;
	const int BUTTON_OFFSET_Y = 100;
	const int RESULT_FONT_SIZE = 72;
	const int SMALL_FONT_SIZE = 42;
	int mResult = 0;
};