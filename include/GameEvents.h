#pragma once

#include <Event.h>
#include <Vector2D.h>
#include <InputEvents.h>
#include "Unit.h"

enum GameEventType
{
	MOVE_EVENT = InputEventType::KEY_PRESSED_EVENT + 1,
	COLLISION_EVENT,
	CLICK_EVENT,
	DISPLAY_ESCAPE_MENU_EVENT
};

class MoveEvent : public Event
{
public:
	MoveEvent(const Vector2D& direction);
	~MoveEvent() {};
	Vector2D getDirection() const { return mDirection; };
private:
	Vector2D mDirection;
};

class CollisionEvent : public Event
{
public:
	CollisionEvent(Unit* unit);
	~CollisionEvent() {};
	Unit* getUnit() const { return mpUnit; };
private:
	Unit* mpUnit;
};

class ClickEvent : public Event
{
public:
	ClickEvent(const Vector2D& position);
	~ClickEvent() {};
	Vector2D getPosition() const { return mPosition; };
private:
	Vector2D mPosition;
};

class DisplayEscapeMenuEvent : public Event
{
public:
	DisplayEscapeMenuEvent();
	~DisplayEscapeMenuEvent() {};
};