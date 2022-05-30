#include "InputSystem.h"
#include <EventSystem.h>
#include "InputEvents.h"
#include <iostream>

using namespace std;

bool InputSystem::init()
{
	if (!al_install_mouse())
	{
		cout << "error installing mouse\n";
		return false;
	}

	if (!al_install_keyboard())
	{
		cout << "error installing keyboard\n";
		return false;
	}

	mpEventQueue = al_create_event_queue();
	if (mpEventQueue == NULL) {
		return false;
	}
	al_register_event_source(mpEventQueue, al_get_keyboard_event_source());
	al_register_event_source(mpEventQueue, al_get_mouse_event_source());

	mIsInitted = true;
	return true;
}

void InputSystem::cleanup()
{
	if (mIsInitted)
	{
		al_uninstall_mouse;
		al_uninstall_keyboard;
		al_unregister_event_source(mpEventQueue, al_get_keyboard_event_source());
		al_unregister_event_source(mpEventQueue, al_get_mouse_event_source());
		al_destroy_event_queue(mpEventQueue);
		mIsInitted = false;
	}
}

void InputSystem::update()
{
	ALLEGRO_EVENT e;
	while (al_get_next_event(mpEventQueue, &e)) {
		switch (e.type) {
			case ALLEGRO_EVENT_KEY_DOWN: {
				KeyPressedEvent event(static_cast<Key>(e.keyboard.keycode), PRESSED);
				EventSystem::getInstance()->fireEvent(event);
				break;
			}
			case ALLEGRO_EVENT_KEY_UP: {
				KeyPressedEvent event(static_cast<Key>(e.keyboard.keycode), RELEASED);
				EventSystem::getInstance()->fireEvent(event);
				break;
			}
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
				MousePressedEvent event(Vector2D(e.mouse.x, e.mouse.y), static_cast<MouseButton>(e.mouse.button), PRESSED);
				EventSystem::getInstance()->fireEvent(event);
				break;
			}
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
				MousePressedEvent event(Vector2D(e.mouse.x, e.mouse.y), static_cast<MouseButton>(e.mouse.button), RELEASED);
				EventSystem::getInstance()->fireEvent(event);
				break;
			}
			case ALLEGRO_EVENT_MOUSE_AXES: {
				MouseMoveEvent event(Vector2D(e.mouse.x, e.mouse.y));
				EventSystem::getInstance()->fireEvent(event);
				break;
			}
		}
	}
}
