#pragma once
#include "Menu.h"

class MapMenu : public Menu
{
public:
	MapMenu() {};
	void init();
	void render(std::unordered_map<std::string, std::string>& words);
	void handleEvent(const Event& theEvent);
private:
	const std::string mTextKeys[5] = { "Default", "Rock", "Portal", "Both", "Back" };

	const std::string BACKGROUND = "logoless-menu.png";
	const std::string DEFAULT_MAP_PREVIEW = "default-map-preview.png";
	const std::string ROCK_MAP_PREVIEW = "rock-map-preview.png";
	const std::string PORTAL_MAP_PREVIEW = "portal-map-preview.png";
	const std::string ROCK_AND_PORTAL_MAP_PREVIEW = "rock-and-portal-map-preview.png";

	const std::string MAP_PATH = "maps/";
	const std::string DEFAULT_MAP_FILENAME = "default.csv";
	const std::string ROCK_MAP_FILENAME = "rocks.csv";
	const std::string PORTAL_MAP_FILENAME = "portals.csv";
	const std::string ROCK_AND_PORTAL_MAP_FILENAME = "rocks-and-portals.csv";

	const int MAP_PREVIEW_WIDTH = 256;
	const int MAP_PREVIEW_HEIGHT = 256;
	const int IMG_ALIGN_X = (CANVAS_WIDTH / 3) - (MAP_PREVIEW_WIDTH / 2);
	const int IMG_ALIGN_Y = (CANVAS_HEIGHT / 3) - (MAP_PREVIEW_HEIGHT / 2) - 50;
	const int BUTTON_ALIGN_X = (CANVAS_WIDTH / 2) - (BUTTON_WIDTH / 2);
	const int BUTTON_ALIGN_Y = 855;
};

