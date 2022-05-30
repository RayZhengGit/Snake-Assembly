#pragma once

#include <Trackable.h>
#include <vector>
#include <Sprite.h>

class Animation : public Trackable
{
public:
	Animation() {};
	Animation(float timeBetweenSprites, bool shouldLoop);
	~Animation() {};
	void addSprite(Sprite sprite);
	void update(float deltaTime);
	void increaseSpeed(float amount);
	void decreaseSpeed(float amount);
	Sprite getCurrentSprite() const { return mSprites[mCurrentSpriteIndex]; };
	int getWidth() const { return getCurrentSprite().getWidth(); };
	int getHeight() const { return getCurrentSprite().getHeight(); };
private:
	std::vector<Sprite> mSprites;
	unsigned int mCurrentSpriteIndex;
	float mTimeBetweenSprites;
	float mTimeUntilNextSprite;
	bool mShouldLoop;
};