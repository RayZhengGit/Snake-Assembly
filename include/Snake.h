#pragma once

#include <Trackable.h>
#include <vector>
#include "Unit.h"
#include <Vector2D.h>

class Snake : public Trackable
{
public:
	Snake() {};
	~Snake();
	void init(int pixelDiff);
	void clear();
	void update(float deltaTime);
	void draw();
	void move();
	void grow(Unit* unit);
	void updateAnimations();
	Vector2D getDirection() const { return mDirection; };
	void changeDirection(const Vector2D& direction);
	int getSize() const { return mUnits.size(); };
	std::vector<Unit*> getUnits() const { return mUnits; };
	Unit* getUnit(int index) const { return mUnits[index]; };
	Unit* getHead() const { return mUnits[0]; };
	Unit* getTail() const { return mUnits[mUnits.size() - 1]; };
	Vector2D getHeadLocation() { return getHead()->getLocation(); };
	Vector2D getBehindTailLocation();
	Vector2D getSnakeUnitLocation(int index);
	bool occupyingLocation(const Vector2D& checkingLocation);
private:
	Vector2D mDirection = Vector2D(1, 0);
	std::vector<Unit*> mUnits;
	float mPixelDiff;
};