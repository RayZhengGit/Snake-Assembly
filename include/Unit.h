#pragma once

#include <Trackable.h>
#include <Vector2D.h>
#include "Animation.h"
#include <GraphicsSystem.h>
#include <unordered_map>

enum UnitType {
	DEFAULT = -1,
	EMPTY,
	SNAKE,
	APPLE,
	ROCK,
	SNAIL,
	GHOST,
	PORTAL
};

class Unit : public Trackable
{
public:
	Unit(const Vector2D& location, UnitType type = UnitType::DEFAULT);
	~Unit();
	void update(float deltaTime);
	void draw();
	void addAnimation(const std::string& key, Animation* animation);
	void removeAnimation(const std::string& key);
	void clearAnimations();
	bool isClicked(const Vector2D& mousePosition);
	Vector2D getLocation() const { return mLocation; };
	void setLocation(const Vector2D& location) { mLocation = location; };
	UnitType getType() const { return mType; };
	std::string getCurrentAnimationKey() const { return mCurrentAnimationKey; };
	Animation* getCurrentAnimation() const { return mAnimations.at(mCurrentAnimationKey); };
	void setCurrentAnimation(const std::string& key) { mCurrentAnimationKey = key; };
private:
	UnitType mType;
	Vector2D mLocation;
	std::unordered_map<std::string, Animation*> mAnimations;
	std::string mCurrentAnimationKey;
};