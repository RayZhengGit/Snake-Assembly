#include "UnitManager.h"

UnitManager::~UnitManager()
{
	clear();
}

void UnitManager::addUnit(Unit* unit)
{
	mUnits.push_back(unit);
}

void UnitManager::removeUnit(Unit* unit)
{
	auto position = std::find(mUnits.begin(), mUnits.end(), unit);
	if (position != mUnits.end()) {
		delete unit;
		mUnits.erase(position);
	}
}

void UnitManager::update(float deltaTime)
{
	if (mIsAnimating) {
		for (Unit* unit : mUnits) {
			unit->update(deltaTime);
		}
	}
}

void UnitManager::draw()
{
	for (Unit* unit : mUnits) {
		unit->draw();
	}
}

void UnitManager::clear()
{
	for (Unit* unit : mUnits) {
		delete unit;
	}
	mUnits.clear();
}

void UnitManager::removeNonMapUnits()
{
	for (int i = 0; i < mUnits.size(); i++) {
		UnitType type = mUnits[i]->getType();
		if (type == UnitType::APPLE || type == UnitType::SNAIL || type == UnitType::GHOST) {
			removeUnit(mUnits[i]);
			i--;
		}
	}
}

bool UnitManager::occupyingLocation(const Vector2D& checkingLocation)
{
	for (int i = 0; i < mUnits.size(); i++) {
		if (mUnits[i]->getLocation() == checkingLocation) {
			return true;
		}
	}
	return false;
}

int UnitManager::getMapUnitCount() const
{
	int result = 0;
	for (Unit* unit : mUnits) {
		UnitType type = unit->getType();
		if (type == UnitType::ROCK || type == UnitType::PORTAL) {
			result++;
		}
	}
	return result;
}
