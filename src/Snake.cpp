#include "Snake.h"
#include "Game.h"
#include <cmath>

Snake::~Snake()
{
	clear();
}

void Snake::init(int pixelDiff)
{
	mPixelDiff = pixelDiff;
}

void Snake::clear()
{
	for (Unit* unit : mUnits) {
		delete unit;
	}
	mUnits.clear();
}

void Snake::update(float deltaTime)
{
	move();
	updateAnimations();

	for (Unit* unit : mUnits) {
		unit->update(deltaTime);
	}
}

void Snake::draw()
{
	for (Unit* unit : mUnits) {
		unit->draw();
	}
}

void Snake::move()
{
	for (int i = mUnits.size() - 1; i >= 1; i--) {
		mUnits[i]->setLocation(mUnits[i - 1]->getLocation());
	}
	mUnits[0]->setLocation(mUnits[0]->getLocation() + mDirection * mPixelDiff);
}

void Snake::grow(Unit* unit)
{
	mUnits.push_back(unit);
}

void Snake::updateAnimations()
{
	// Tail
	Unit* tailUnit = mUnits[mUnits.size() - 1];
	Vector2D nextTailUnitLocation = mUnits[mUnits.size() - 2]->getLocation();
	if (Vector2D::getDistanceBetween(tailUnit->getLocation(), nextTailUnitLocation) != mPixelDiff) {
		nextTailUnitLocation = Game::getInstance()->getNeighboringPortalLocation(tailUnit->getLocation());
	}

	if (tailUnit->getLocation().getX() < nextTailUnitLocation.getX()) {
		tailUnit->setCurrentAnimation("Tail - Right");
	}
	else if (tailUnit->getLocation().getX() > nextTailUnitLocation.getX()) {
		tailUnit->setCurrentAnimation("Tail - Left");
	}
	else if (tailUnit->getLocation().getY() < nextTailUnitLocation.getY()) {
		tailUnit->setCurrentAnimation("Tail - Down");
	}
	else if (tailUnit->getLocation().getY() > nextTailUnitLocation.getY()) {
		tailUnit->setCurrentAnimation("Tail - Up");
	}

	// Body
	for (int i = mUnits.size() - 2; i >= 1; i--) {
		Unit* bodyUnit = mUnits[i];
		Vector2D bodyUnitLocation = bodyUnit->getLocation();
		Vector2D previousUnitLocation = mUnits[i + 1]->getLocation();
		if (Vector2D::getDistanceBetween(bodyUnitLocation, previousUnitLocation) != mPixelDiff) {
			previousUnitLocation = Game::getInstance()->getNeighboringPortalLocation(bodyUnitLocation);
		}
		Vector2D nextUnitLocation = mUnits[i - 1]->getLocation();
		if (Vector2D::getDistanceBetween(bodyUnitLocation, nextUnitLocation) != mPixelDiff) {
			nextUnitLocation = Game::getInstance()->getNeighboringPortalLocation(bodyUnitLocation);
		}

		if ((previousUnitLocation.getX() < bodyUnitLocation.getX() && nextUnitLocation.getX() > bodyUnitLocation.getX()) ||
			(nextUnitLocation.getX() < bodyUnitLocation.getX() && previousUnitLocation.getX() > bodyUnitLocation.getX()))
		{
			bodyUnit->setCurrentAnimation("Body - Across");
		}
		else if ((previousUnitLocation.getY() < bodyUnitLocation.getY() && nextUnitLocation.getY() > bodyUnitLocation.getY()) ||
			(nextUnitLocation.getY() < bodyUnitLocation.getY() && previousUnitLocation.getY() > bodyUnitLocation.getY()))
		{
			bodyUnit->setCurrentAnimation("Body - Down");
		}
		else if ((previousUnitLocation.getX() < bodyUnitLocation.getX() && nextUnitLocation.getY() > bodyUnitLocation.getY()) ||
			(nextUnitLocation.getX() < bodyUnitLocation.getX() && previousUnitLocation.getY() > bodyUnitLocation.getY()))
		{
			bodyUnit->setCurrentAnimation("Body - Turn Top Right");
		}
		else if ((previousUnitLocation.getY() < bodyUnitLocation.getY() && nextUnitLocation.getX() < bodyUnitLocation.getX()) ||
			(nextUnitLocation.getY() < bodyUnitLocation.getY() && previousUnitLocation.getX() < bodyUnitLocation.getX()))
		{
			bodyUnit->setCurrentAnimation("Body - Turn Bottom Right");
		}
		else if ((previousUnitLocation.getX() > bodyUnitLocation.getX() && nextUnitLocation.getY() < bodyUnitLocation.getY()) ||
			(nextUnitLocation.getX() > bodyUnitLocation.getX() && previousUnitLocation.getY() < bodyUnitLocation.getY()))
		{
			bodyUnit->setCurrentAnimation("Body - Turn Bottom Left");
		}
		else if ((previousUnitLocation.getY() > bodyUnitLocation.getY() && nextUnitLocation.getX() > bodyUnitLocation.getX()) ||
			(nextUnitLocation.getY() > bodyUnitLocation.getY() && previousUnitLocation.getX() > bodyUnitLocation.getX()))
		{
			bodyUnit->setCurrentAnimation("Body - Turn Top Left");
		}
	}
	
	// Head
	Unit* headUnit = mUnits[0];
	if (mDirection.getX() == 1) {
		headUnit->setCurrentAnimation("Head - Right");
	}
	else if (mDirection.getX() == -1) {
		headUnit->setCurrentAnimation("Head - Left");
	}
	else if (mDirection.getY() == 1) {
		headUnit->setCurrentAnimation("Head - Down");
	}
	else if (mDirection.getY() == -1) {
		headUnit->setCurrentAnimation("Head - Up");
	}
}

void Snake::changeDirection(const Vector2D& direction)
{
	mDirection = direction;
}

Vector2D Snake::getBehindTailLocation()
{
	Unit* tail = getTail();
	Vector2D tailLocation = tail->getLocation();
	std::string directionStr = tail->getCurrentAnimationKey().substr(7);
	if (directionStr == "Right") {
		return Vector2D(tailLocation.getX() - mPixelDiff, tailLocation.getY());
	}
	else if (directionStr == "Left"){
		return Vector2D(tailLocation.getX() + mPixelDiff, tailLocation.getY());
	}
	else if (directionStr == "Up") {
		return Vector2D(tailLocation.getX(), tailLocation.getY() + mPixelDiff);
	}
	else if (directionStr == "Down") {
		return Vector2D(tailLocation.getX(), tailLocation.getY() - mPixelDiff);
	}
}

Vector2D Snake::getSnakeUnitLocation(int index)
{
	return mUnits[index]->getLocation();
}

bool Snake::occupyingLocation(const Vector2D& checkingLocation)
{
	for (int i = 0; i < mUnits.size(); i++) {
		if (mUnits[i]->getLocation() == checkingLocation) {
			return true;
		}
	}
	return false;
}
