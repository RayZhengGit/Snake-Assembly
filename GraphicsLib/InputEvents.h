#pragma once

#include <Event.h>
#include <Vector2D.h>
#include <allegro5/allegro.h>

enum InputEventType
{
	MOUSE_MOVE_EVENT = EventType::NUM_BASE_EVENT_TYPES + 1,
	MOUSE_PRESSED_EVENT,
	KEY_PRESSED_EVENT
};

enum Key
{
	ESCAPE = ALLEGRO_KEY_ESCAPE,
	W = ALLEGRO_KEY_W,
	A = ALLEGRO_KEY_A,
	S = ALLEGRO_KEY_S,
	D = ALLEGRO_KEY_D,
	ARROW_LEFT = ALLEGRO_KEY_LEFT,
	ARROW_RIGHT = ALLEGRO_KEY_RIGHT,
	ARROW_UP = ALLEGRO_KEY_UP,
	ARROW_DOWN = ALLEGRO_KEY_DOWN
};

enum MouseButton
{
	LEFT = 1,
	RIGHT = 2,
	CENTER = 4
};

enum State
{
	PRESSED,
	RELEASED
};

class MouseMoveEvent : public Event
{
public:
	MouseMoveEvent(Vector2D location);
	~MouseMoveEvent() {};
	Vector2D getLocation() const { return mLocation; }
private:
	Vector2D mLocation;
};

class MousePressedEvent : public Event
{
public:
	MousePressedEvent(Vector2D location, MouseButton mouseButton, State state);
	~MousePressedEvent() {};
	Vector2D getLocation() const { return mLocation; }
	MouseButton getMouseButton() const { return mMouseButton; }
	State getState() const { return mState; }
private:
	Vector2D mLocation;
	MouseButton mMouseButton;
	State mState;
};

class KeyPressedEvent : public Event
{
public:
	KeyPressedEvent(Key key, State state);
	~KeyPressedEvent() {};
	Key getKey() const { return mKey; }
	State getState() const { return mState; }
private:
	Key mKey;
	State mState;
};
