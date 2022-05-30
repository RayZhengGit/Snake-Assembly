#pragma once
#include "Sound.h"
#include <unordered_map>

class SoundSystem
{
public:
	SoundSystem() {};
	~SoundSystem();
	void init();
	void addSound(const std::string key, const std::string filePath);
	void playSound(const std::string key, bool shouldLoop);
	void startMusic();
	void stopMusic();
	void enableEffects();
	void disableEffects();

private:
	const float MUSIC_VOLUME = 0.05;
	const float DEFAULT_EFFECT_VOLUME = 0.15;
	float mEffectVolume = DEFAULT_EFFECT_VOLUME; // constant to reset value

	const std::string AUDIO_PATH = "assets/audio/";
	const std::string MUSIC = "snake-theme.ogg";
	const std::string BUTTON_CLICK = "button-click.ogg";
	const std::string APPLE_EFFECT = "crunch.ogg";
	const std::string POWERUP_EFFECT = "power-up.ogg";
	const std::string PORTAL_EFFECT = "portal.ogg";
	const std::string LOSE_EFFECT = "lose-game.ogg";
	
	std::unordered_map<std::string, Sound*> mSounds;
};