#pragma once
#include "Unit.h"
#include "GraphicsBufferManager.h"

// Factory Method Design Pattern
// Credit: https://medium.com/@digit.sensitivee/game-programming-patterns-the-factory-method-87d7f8c12081
class UnitFactory {
public:
	void init(int unitPixelSize);
	Unit* createUnit(UnitType type, const Vector2D& location);
	void resetPortalCount() { mPortalCount = 0; };
private:
	GraphicsBufferManager* mpGraphicsBufferManager;
	int mUnitPixelSize;
	int mPortalCount = 0;
	Unit* createSnakeUnit(const Vector2D& location);
	Unit* createAppleUnit(const Vector2D& location);
	Unit* createRockUnit(const Vector2D& location);
	Unit* createSnailUnit(const Vector2D& location);
	Unit* createGhostUnit(const Vector2D& location);
	Unit* createPortalUnit(const Vector2D& location);
};