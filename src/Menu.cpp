#include "Menu.h"
#include "Game.h"
#include <EventSystem.h>
#include "GameEvents.h"

Menu::~Menu()
{
	EventSystem::getInstance()->removeListener((EventType)CLICK_EVENT, this);
	delete mpFont;
	mpFont = nullptr;

	for (Unit* unit : mButtons) {
		delete unit;
	}
	mButtons.clear();
}

void Menu::init()
{
	EventSystem::getInstance()->addListener((EventType)CLICK_EVENT, this);
	mpSystem = Game::getInstance()->getSystem();
	mpGraphicsBufferManager = Game::getInstance()->getGraphicsBufferManager();
	mpSoundSystem = Game::getInstance()->getSoundSystem();
	mpFont = new Font(ASSET_PATH + FONT, FONT_SIZE);
}

void Menu::update(float deltaTime)
{
	for (Unit* unit : mButtons) {
		unit->update(deltaTime);
	}
}

void Menu::addButtonUnit(const Vector2D& location)
{
	Animation* animation = new Animation(180.0f, true);
	animation->addSprite({ mpGraphicsBufferManager->getGraphicsBuffer("Button"), Vector2D(0, 0), BUTTON_WIDTH, BUTTON_HEIGHT });

	Unit* unit = new Unit(location);
	unit->addAnimation("Button", animation);
	mButtons.push_back(unit);
}

void Menu::addToggleUnit(const Vector2D& location)
{
	Animation* toggleOnAnimation = new Animation(180.0f, true);
	toggleOnAnimation->addSprite({ mpGraphicsBufferManager->getGraphicsBuffer("Green Toggle"), Vector2D(0, 0), TOGGLE_WIDTH, TOGGLE_HEIGHT });

	Animation* toggleOffAnimation = new Animation(180.0f, true);
	toggleOffAnimation->addSprite({ mpGraphicsBufferManager->getGraphicsBuffer("Grey Toggle"), Vector2D(0, 0), TOGGLE_WIDTH, TOGGLE_HEIGHT });

	Unit* unit = new Unit(location);
	unit->addAnimation("Toggle - On", toggleOnAnimation);
	unit->addAnimation("Toggle - Off", toggleOffAnimation);
	mButtons.push_back(unit);
}
