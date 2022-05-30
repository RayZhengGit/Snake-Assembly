#include <iostream>
#include <MemoryTracker.h>
#include "Game.h"
#include <EventSystem.h>

int main()
{
	const unsigned int WIDTH = 1216; // UNIT_WIDTH * COLUMN_NUM + HUD_WIDTH (64 * 16 + 192)
	const unsigned int HEIGHT = 1024; // UNIT_HEIGHT * ROW_NUM (64 * 16)
	const unsigned int FPS = 60;

	EventSystem::initInstance();
	EventSystem::getInstance()->init();
	Game* theGame = Game::getInstance();
	theGame->init(WIDTH, HEIGHT, FPS);
	theGame->doLoop();
	theGame->cleanup();
	EventSystem::cleanupInstance();

	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");
}