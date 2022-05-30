#include "Sound.h"

Sound::Sound(const std::string& filename)
{
	mpSample = al_load_sample(filename.c_str());
	mpSampleId = new ALLEGRO_SAMPLE_ID;
}

Sound::~Sound()
{
	al_destroy_sample(mpSample);
	delete mpSampleId;
}

void Sound::play(float volume, bool shouldLoop)
{
	ALLEGRO_PLAYMODE mode;
	if (shouldLoop) {
		mode = ALLEGRO_PLAYMODE_LOOP;
	}
	else {
		mode = ALLEGRO_PLAYMODE_ONCE;
	}
	al_play_sample(mpSample, volume, 0, 1.0f, mode, mpSampleId);
}

void Sound::stop()
{
	al_stop_sample(mpSampleId);
}
