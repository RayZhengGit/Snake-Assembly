#pragma once

#include <EventListener.h>
#include <Event.h>

class InputTranslator : public EventListener
{
public:
	InputTranslator() {};
	~InputTranslator();
	void init();
	void cleanup();
	void handleEvent(const Event& theEvent);
private:
	bool mIsInitted = false;
};