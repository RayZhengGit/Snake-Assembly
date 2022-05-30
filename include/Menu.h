#pragma once
#include <EventListener.h>
#include "Unit.h"
#include <System.h>
#include "GraphicsBufferManager.h"
#include "SoundSystem.h"
#include <Font.h>
#include <unordered_map>

class Menu : public EventListener
{
public:
	Menu() {};
	~Menu();
	virtual void init();
	virtual void render(std::unordered_map<std::string, std::string>& words) = 0;
	virtual void handleEvent(const Event& theEvent) = 0;
	void update(float deltaTime);
protected:
	std::vector<Unit*> mButtons;
	void addButtonUnit(const Vector2D& location);
	void addToggleUnit(const Vector2D& location);
	System* mpSystem = NULL;
	GraphicsBufferManager* mpGraphicsBufferManager = NULL;
	SoundSystem* mpSoundSystem = NULL;
	Font* mpFont = NULL;
	const std::string FONT = "cour.ttf";
	const std::string ASSET_PATH = "assets/";
	const std::string BUTTON = "button.png";
	const int FONT_SIZE = 48;
	const int CANVAS_WIDTH = 1216;
	const int CANVAS_HEIGHT = 1024;
	const int BUTTON_WIDTH = 300;
	const int BUTTON_HEIGHT = 96;
	const int TOGGLE_WIDTH = 217;
	const int TOGGLE_HEIGHT = 96;
};
