#pragma once

#include "Game.h"
#include <System.h>
#include "GraphicsBufferManager.h"
#include <Font.h>
#include "Unit.h"

class Hud
{
public:
	Hud() {};
	~Hud();
	void init(int unitPixelSize);
	void draw(std::unordered_map<std::string, std::string>& words, int score, bool isGhostActive, bool isSnailActive);
private:
	const std::string mTextKeys[3] = { "Score", "Power-Up", "None" };

	System* mpSystem = NULL;
	GraphicsBufferManager* mpGraphicsBufferManager = NULL;
	Font* mpFont = NULL;
	Unit* mpGhostIconUnit = NULL;
	Unit* mpSnailIconUnit = NULL;
	
	const std::string ASSET_PATH = "assets/";
	const std::string BACKGROUND = "hud-background.jpg";
	const std::string FONT = "cour.ttf";
	const int FONT_SIZE = 38;

	const int START_X = 1024;
	const Vector2D SCORE_LABEL_POSITION = Vector2D(1120, 342);
	const Vector2D SCORE_TEXT_POSITION = SCORE_LABEL_POSITION + Vector2D(0, 50);
	const Vector2D POWER_UP_LABEL_POSITION = Vector2D(1120, 684);
	const Vector2D POWER_UP_ICON_POSITION = POWER_UP_LABEL_POSITION + Vector2D(0, 50);
};