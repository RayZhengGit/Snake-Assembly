#pragma once

#include <Trackable.h>
#include <vector>
#include "Unit.h"

class UnitManager : public Trackable
{
public:
	UnitManager() {};
	~UnitManager();
	void addUnit(Unit* unit);
	void removeUnit(Unit* unit);
	void update(float deltaTime);
	void draw();
	void clear();
	void removeNonMapUnits();
	void toggleIsAnimating() { mIsAnimating = !mIsAnimating; };
	bool occupyingLocation(const Vector2D& checkingLocation);
	std::vector<Unit*> getUnits() const { return mUnits; };
	int getMapUnitCount() const;
private:
	std::vector<Unit*> mUnits;
	bool mIsAnimating = true;
};