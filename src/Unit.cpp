#include "Unit.h"

Unit::Unit(const Vector2D& location, UnitType type)
{
	mLocation = location;
	mType = type;
}

Unit::~Unit()
{
	clearAnimations();
}

void Unit::update(float deltaTime)
{
	getCurrentAnimation()->update(deltaTime);
}

void Unit::draw()
{
	GraphicsSystem::draw(mLocation, getCurrentAnimation()->getCurrentSprite());
}

void Unit::addAnimation(const std::string& key, Animation* animation)
{
	mAnimations[key] = animation;
	if (mAnimations.size() == 1) {
		mCurrentAnimationKey = key;
	}
}

void Unit::removeAnimation(const std::string& key)
{
	delete mAnimations[key];
	mAnimations.erase(key);
}

void Unit::clearAnimations()
{
	for (auto it : mAnimations) {
		delete it.second;
	}
	mAnimations.clear();
}

bool Unit::isClicked(const Vector2D& mousePosition)
{
	float animationWidth = getCurrentAnimation()->getWidth();
	float animationHeight = getCurrentAnimation()->getHeight();
	float diffX = mousePosition.getX() - mLocation.getX();
	float diffY = mousePosition.getY() - mLocation.getY();
	return (diffX >= 0 && diffX <= animationWidth && diffY >= 0 && diffY <= animationHeight);
}
