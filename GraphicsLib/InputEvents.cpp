#include "InputEvents.h"

MouseMoveEvent::MouseMoveEvent(Vector2D location) : Event((EventType)MOUSE_MOVE_EVENT)
{
	mLocation = location;
}

MousePressedEvent::MousePressedEvent(Vector2D location, MouseButton mouseButton, State state) : Event((EventType)MOUSE_PRESSED_EVENT)
{
	mLocation = location;
	mMouseButton = mouseButton;
	mState = state;
}

KeyPressedEvent::KeyPressedEvent(Key key, State state) : Event((EventType)KEY_PRESSED_EVENT)
{
	mKey = key;
	mState = state;
}
