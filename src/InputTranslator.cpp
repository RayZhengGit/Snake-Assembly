#include "InputTranslator.h"
#include <EventSystem.h>
#include <InputSystem.h>
#include <InputEvents.h>
#include "GameEvents.h"

InputTranslator::~InputTranslator()
{
	cleanup();
}

void InputTranslator::init()
{
	if (!mIsInitted)
	{
		EventSystem::getInstance()->addListener((EventType)MOUSE_MOVE_EVENT, this);
		EventSystem::getInstance()->addListener((EventType)MOUSE_PRESSED_EVENT, this);
		EventSystem::getInstance()->addListener((EventType)KEY_PRESSED_EVENT, this);
		mIsInitted = true;
	}
}

void InputTranslator::cleanup()
{
	if (mIsInitted)
	{
		EventSystem::getInstance()->removeListener((EventType)MOUSE_MOVE_EVENT, this);
		EventSystem::getInstance()->removeListener((EventType)MOUSE_PRESSED_EVENT, this);
		EventSystem::getInstance()->removeListener((EventType)KEY_PRESSED_EVENT, this);
		mIsInitted = false;
	}
}

void InputTranslator::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == KEY_PRESSED_EVENT) {
		const KeyPressedEvent& inputEvent = static_cast<const KeyPressedEvent&>(theEvent);

		if (inputEvent.getState() == PRESSED) {
			if (inputEvent.getKey() == Key::W || inputEvent.getKey() == Key::ARROW_UP) {
				MoveEvent event(Vector2D(0, -1));
				EventSystem::getInstance()->fireEvent(event);
			}
			else if (inputEvent.getKey() == Key::A || inputEvent.getKey() == Key::ARROW_LEFT) {
				MoveEvent event(Vector2D(-1, 0));
				EventSystem::getInstance()->fireEvent(event);
			}
			else if (inputEvent.getKey() == Key::S || inputEvent.getKey() == Key::ARROW_DOWN) {
				MoveEvent event(Vector2D(0, 1));
				EventSystem::getInstance()->fireEvent(event);
			}
			else if (inputEvent.getKey() == Key::D || inputEvent.getKey() == Key::ARROW_RIGHT) {
				MoveEvent event(Vector2D(1, 0));
				EventSystem::getInstance()->fireEvent(event);
			}
			else if (inputEvent.getKey() == Key::ESCAPE) {
				DisplayEscapeMenuEvent event;
				EventSystem::getInstance()->fireEvent(event);
			}
		}
	}
	else if (theEvent.getType() == MOUSE_PRESSED_EVENT) {
		const MousePressedEvent& inputEvent = static_cast<const MousePressedEvent&>(theEvent);
		if (inputEvent.getMouseButton() == MouseButton::LEFT && inputEvent.getState() == State::PRESSED) {
			ClickEvent event(inputEvent.getLocation());
			EventSystem::getInstance()->fireEvent(event);
		}
	}
}
