#include "Hud.h"

Hud::~Hud()
{
	delete mpFont;
	delete mpGhostIconUnit;
	delete mpSnailIconUnit;
}

void Hud::init(int unitPixelSize)
{
	mpSystem = Game::getInstance()->getSystem();
	mpGraphicsBufferManager = Game::getInstance()->getGraphicsBufferManager();
	mpGraphicsBufferManager->addGraphicsBuffer("HUD Background", new GraphicsBuffer(ASSET_PATH + BACKGROUND));
	mpFont = new Font(ASSET_PATH + FONT, FONT_SIZE);

	GraphicsBuffer* ghostBuffer = mpGraphicsBufferManager->getGraphicsBuffer("Ghost");
	Animation* ghostAnimation = new Animation(180.0f, true);
	ghostAnimation->addSprite({ ghostBuffer, Vector2D(0, 0), unitPixelSize, unitPixelSize });
	mpGhostIconUnit = new Unit(POWER_UP_ICON_POSITION - Vector2D(unitPixelSize / 2, 0));
	mpGhostIconUnit->addAnimation("Snail", ghostAnimation);

	GraphicsBuffer* snailBuffer = mpGraphicsBufferManager->getGraphicsBuffer("Snail");
	Animation* snailAnimation = new Animation(180.0f, true);
	snailAnimation->addSprite({ snailBuffer, Vector2D(0, 0), unitPixelSize, unitPixelSize });
	mpSnailIconUnit = new Unit(POWER_UP_ICON_POSITION - Vector2D(unitPixelSize / 2, 0));
	mpSnailIconUnit->addAnimation("Snail", snailAnimation);
}

void Hud::draw(std::unordered_map<std::string, std::string>& words, int score, bool isGhostActive, bool isSnailActive)
{
	mpSystem->getGraphicsSystem()->draw(Vector2D(START_X, 0), *mpGraphicsBufferManager->getGraphicsBuffer("HUD Background"));
	mpSystem->getGraphicsSystem()->writeText(SCORE_LABEL_POSITION, *mpFont, Color(255, 255, 255), words[mTextKeys[0]], Font::CENTER);
	mpSystem->getGraphicsSystem()->writeText(SCORE_TEXT_POSITION, *mpFont, Color(255, 255, 255), to_string(score), Font::CENTER);
	mpSystem->getGraphicsSystem()->writeText(POWER_UP_LABEL_POSITION, *mpFont, Color(255, 255, 255), words[mTextKeys[1]], Font::CENTER);

	if (isGhostActive) {
		mpGhostIconUnit->draw();
	}
	else if (isSnailActive) {
		mpSnailIconUnit->draw();
	}
	else {
		mpSystem->getGraphicsSystem()->writeText(POWER_UP_ICON_POSITION, *mpFont, Color(255, 255, 255), words[mTextKeys[2]], Font::CENTER);
	}
}