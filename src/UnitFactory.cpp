#include "UnitFactory.h"
#include "Game.h"

void UnitFactory::init(int unitPixelSize)
{
	mpGraphicsBufferManager = Game::getInstance()->getGraphicsBufferManager();
	mUnitPixelSize = unitPixelSize;
}

Unit* UnitFactory::createUnit(UnitType type, const Vector2D& location)
{
	switch (type)
	{
		case SNAKE:
			return createSnakeUnit(location);
		case APPLE:
			return createAppleUnit(location);
		case ROCK:
			return createRockUnit(location);
		case SNAIL:
			return createSnailUnit(location);
		case GHOST:
			return createGhostUnit(location);
		case PORTAL:
			return createPortalUnit(location);
	}
}

Unit* UnitFactory::createSnakeUnit(const Vector2D& location)
{
	GraphicsBuffer* buffer = mpGraphicsBufferManager->getGraphicsBuffer("Snake Graphics");

	// Head
	Animation* rightHeadAnimation = new Animation(180.0f, true);
	Animation* leftHeadAnimation = new Animation(180.0f, true);
	Animation* upHeadAnimation = new Animation(180.0f, true);
	Animation* downHeadAnimation = new Animation(180.0f, true);
	rightHeadAnimation->addSprite({ buffer, Vector2D(4 * mUnitPixelSize, 0), mUnitPixelSize, mUnitPixelSize });
	leftHeadAnimation->addSprite({ buffer, Vector2D(3 * mUnitPixelSize, mUnitPixelSize), mUnitPixelSize, mUnitPixelSize });
	upHeadAnimation->addSprite({ buffer, Vector2D(3 * mUnitPixelSize, 0), mUnitPixelSize, mUnitPixelSize });
	downHeadAnimation->addSprite({ buffer, Vector2D(4 * mUnitPixelSize, mUnitPixelSize), mUnitPixelSize, mUnitPixelSize });

	// Body
	Animation* acrossBodyAnimation = new Animation(180.0f, true);
	Animation* downBodyAnimation = new Animation(180.0f, true);
	Animation* turnTopLeftBodyAnimation = new Animation(180.0f, true);
	Animation* turnTopRightBodyAnimation = new Animation(180.0f, true);
	Animation* turnBottomRightBodyAnimation = new Animation(180.0f, true);
	Animation* turnBottomLeftBodyAnimation = new Animation(180.0f, true);
	acrossBodyAnimation->addSprite({ buffer, Vector2D(mUnitPixelSize, 0), mUnitPixelSize, mUnitPixelSize });
	downBodyAnimation->addSprite({ buffer, Vector2D(2 * mUnitPixelSize, mUnitPixelSize), mUnitPixelSize, mUnitPixelSize });
	turnTopLeftBodyAnimation->addSprite({ buffer, Vector2D(0, 0), mUnitPixelSize, mUnitPixelSize });
	turnTopRightBodyAnimation->addSprite({ buffer, Vector2D(2 * mUnitPixelSize, 0), mUnitPixelSize, mUnitPixelSize });
	turnBottomRightBodyAnimation->addSprite({ buffer, Vector2D(2 * mUnitPixelSize, 2 * mUnitPixelSize), mUnitPixelSize, mUnitPixelSize });
	turnBottomLeftBodyAnimation->addSprite({ buffer, Vector2D(0, mUnitPixelSize), mUnitPixelSize, mUnitPixelSize });

	// Tail
	Animation* rightTailAnimation = new Animation(180.0f, true);
	Animation* leftTailAnimation = new Animation(180.0f, true);
	Animation* upTailAnimation = new Animation(180.0f, true);
	Animation* downTailAnimation = new Animation(180.0f, true);
	rightTailAnimation->addSprite({ buffer, Vector2D(4 * mUnitPixelSize, 2 * mUnitPixelSize), mUnitPixelSize, mUnitPixelSize });
	leftTailAnimation->addSprite({ buffer, Vector2D(3 * mUnitPixelSize, 3 * mUnitPixelSize), mUnitPixelSize, mUnitPixelSize });
	upTailAnimation->addSprite({ buffer, Vector2D(3 * mUnitPixelSize, 2 * mUnitPixelSize), mUnitPixelSize, mUnitPixelSize });
	downTailAnimation->addSprite({ buffer, Vector2D(4 * mUnitPixelSize, 3 * mUnitPixelSize), mUnitPixelSize, mUnitPixelSize });

	Unit* unit = new Unit(location, UnitType::SNAKE);
	unit->addAnimation("Head - Right", rightHeadAnimation);
	unit->addAnimation("Head - Left", leftHeadAnimation);
	unit->addAnimation("Head - Up", upHeadAnimation);
	unit->addAnimation("Head - Down", downHeadAnimation);
	unit->addAnimation("Body - Across", acrossBodyAnimation);
	unit->addAnimation("Body - Down", downBodyAnimation);
	unit->addAnimation("Body - Turn Top Left", turnTopLeftBodyAnimation);
	unit->addAnimation("Body - Turn Top Right", turnTopRightBodyAnimation);
	unit->addAnimation("Body - Turn Bottom Right", turnBottomRightBodyAnimation);
	unit->addAnimation("Body - Turn Bottom Left", turnBottomLeftBodyAnimation);
	unit->addAnimation("Tail - Right", rightTailAnimation);
	unit->addAnimation("Tail - Left", leftTailAnimation);
	unit->addAnimation("Tail - Up", upTailAnimation);
	unit->addAnimation("Tail - Down", downTailAnimation);
	return unit;
}

Unit* UnitFactory::createAppleUnit(const Vector2D& location)
{
	GraphicsBuffer* buffer = mpGraphicsBufferManager->getGraphicsBuffer("Snake Graphics");
	Animation* animation = new Animation(180.0f, true);
	animation->addSprite({ buffer, Vector2D(0, 3 * mUnitPixelSize), mUnitPixelSize, mUnitPixelSize });

	Unit* unit = new Unit(location, UnitType::APPLE);
	unit->addAnimation("Apple", animation);
	return unit;
}

Unit* UnitFactory::createRockUnit(const Vector2D& location)
{
	GraphicsBuffer* buffer = mpGraphicsBufferManager->getGraphicsBuffer("Rock");
	Animation* animation = new Animation(180.0f, true);
	animation->addSprite({ buffer, Vector2D(0, 0), mUnitPixelSize, mUnitPixelSize });

	Unit* unit = new Unit(location, UnitType::ROCK);
	unit->addAnimation("Rock", animation);
	return unit;
}

Unit* UnitFactory::createSnailUnit(const Vector2D& location)
{
	GraphicsBuffer* buffer = mpGraphicsBufferManager->getGraphicsBuffer("Snail");
	Animation* animation = new Animation(180.0f, true);
	animation->addSprite({ buffer, Vector2D(0, 0), mUnitPixelSize, mUnitPixelSize });

	Unit* unit = new Unit(location, UnitType::SNAIL);
	unit->addAnimation("Snail", animation);
	return unit;
}

Unit* UnitFactory::createGhostUnit(const Vector2D& location)
{
	GraphicsBuffer* buffer = mpGraphicsBufferManager->getGraphicsBuffer("Ghost");
	Animation* animation = new Animation(180.0f, true);
	animation->addSprite({ buffer, Vector2D(0, 0), mUnitPixelSize, mUnitPixelSize });

	Unit* unit = new Unit(location, UnitType::GHOST);
	unit->addAnimation("Ghost", animation);
	return unit;
}

Unit* UnitFactory::createPortalUnit(const Vector2D& location)
{
	string bufferKey;
	if (mPortalCount < 2) {
		bufferKey = "Purple Portal";
	} else if (mPortalCount < 4) {
		bufferKey = "Blue Portal";
	} else {
		bufferKey = "Red Portal";
	}
	GraphicsBuffer* buffer = mpGraphicsBufferManager->getGraphicsBuffer(bufferKey);

	Animation* animation = new Animation(180.0f, true);
	animation->addSprite({ buffer, Vector2D(0, 0), mUnitPixelSize, mUnitPixelSize });

	Unit* unit = new Unit(location, UnitType::PORTAL);
	unit->addAnimation("Portal", animation);
	mPortalCount++;
	return unit;
}
