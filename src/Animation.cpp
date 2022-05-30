#include "Animation.h"

Animation::Animation(float timeBetweenSprites, bool shouldLoop)
{
	mTimeBetweenSprites = timeBetweenSprites;
	mTimeUntilNextSprite = timeBetweenSprites;
	mShouldLoop = shouldLoop;
	mCurrentSpriteIndex = 0;
}

void Animation::addSprite(Sprite sprite)
{
	mSprites.push_back(sprite);
}

void Animation::update(float deltaTime)
{
	mTimeUntilNextSprite -= deltaTime;

	if (mTimeUntilNextSprite <= 0) {
		mTimeUntilNextSprite = mTimeBetweenSprites;

		if (mCurrentSpriteIndex < mSprites.size() - 1) {
			mCurrentSpriteIndex++;
		}
		else if (mShouldLoop) {
			mCurrentSpriteIndex = 0;
		}
	}
}

void Animation::increaseSpeed(float amount)
{
	if (mTimeBetweenSprites >= amount)
	{
		mTimeBetweenSprites -= amount;
	}
}

void Animation::decreaseSpeed(float amount)
{
	mTimeBetweenSprites += amount;
}
