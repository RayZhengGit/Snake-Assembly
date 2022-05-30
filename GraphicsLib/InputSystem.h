#pragma once

#include <Trackable.h>
#include <allegro5/allegro.h>

class InputSystem : public Trackable
{
public:
	InputSystem() {};
	~InputSystem() {};
	bool init();
	void cleanup();
	void update();
private:
	bool mIsInitted = false;
	ALLEGRO_EVENT_QUEUE* mpEventQueue = NULL;
};
