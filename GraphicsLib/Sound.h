#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <Trackable.h>

class Sound : public Trackable
{
public:
	Sound(const std::string& filename);
	~Sound();
	void play(float volume, bool shouldLoop);
	void stop();
private:
	ALLEGRO_SAMPLE* mpSample = NULL;
	ALLEGRO_SAMPLE_ID* mpSampleId = NULL;
};