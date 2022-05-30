#include "SoundSystem.h"
#include "Sound.h"

SoundSystem::~SoundSystem()
{
	for (auto it : mSounds) {
		delete it.second;
	}
	mSounds.clear();
}

void SoundSystem::init()
{
	addSound("Snake Theme", AUDIO_PATH + MUSIC);
	addSound("Button Click", AUDIO_PATH + BUTTON_CLICK);
	addSound("Apple Effect", AUDIO_PATH + APPLE_EFFECT);
	addSound("Power-Up Effect", AUDIO_PATH + POWERUP_EFFECT);
	addSound("Portal Effect", AUDIO_PATH + PORTAL_EFFECT);
	addSound("Lose Effect", AUDIO_PATH + LOSE_EFFECT);
	
	startMusic();
}

void SoundSystem::addSound(const std::string key, const std::string filePath)
{
	mSounds[key] = new Sound(filePath);
}

void SoundSystem::playSound(const std::string key, bool shouldLoop)
{
	float volume;
	if (shouldLoop) {
		volume = MUSIC_VOLUME;
	}
	else {
		volume = mEffectVolume;
	}
	mSounds[key]->play(volume, shouldLoop);
}

void SoundSystem::startMusic()
{
	playSound("Snake Theme", true);
}

void SoundSystem::stopMusic()
{
	mSounds["Snake Theme"]->stop();
}

void SoundSystem::enableEffects()
{
	mEffectVolume = DEFAULT_EFFECT_VOLUME;
}

void SoundSystem::disableEffects()
{
	mEffectVolume = 0;
}
