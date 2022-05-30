#include "System.h"
#include "GraphicsSystem.h"
#include "InputSystem.h"
#include <iostream>

using namespace std;

System::System()
{
	mpGraphicsSystem = new GraphicsSystem;
	mpInputSystem = new InputSystem;
}

System::~System()
{
	cleanup();
	delete mpGraphicsSystem;
	delete mpInputSystem;
}

bool System::init(unsigned int width, unsigned int height)
{
	if (!mIsInitted)
	{
		if (!al_init())
		{
			cout << "error initting Allegro\n";
			return false;
		}
		else
		{
			bool initGraphicsSystemRes = mpGraphicsSystem->init(width, height);
			if (!initGraphicsSystemRes)
			{
				cout << "error initting GraphicsSystem\n";
				return false;
			}

			bool initInputSystemRes = mpInputSystem->init();
			if (!initInputSystemRes)
			{
				cout << "error initting InputSystem\n";
				return false;
			}
		}
		mIsInitted = true;
	}
	return true;
}

void System::cleanup()
{
	if (mIsInitted)
	{
		mpGraphicsSystem->cleanup();
		mpInputSystem->cleanup();
		mIsInitted = false;
	}
}
