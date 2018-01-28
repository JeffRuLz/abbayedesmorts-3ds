#pragma once

#include <3ds.h>

typedef struct
{
	u32 sampleRate;
	u32 size;
	u16 bitsPerSample;
	u16 numChannels;
	u8* data;
} Sound;

#define Music Sound

void aud_Init();
void aud_Exit();

Music* aud_LoadMusic(char* fname);
void aud_FreeMusic(Music* mus);

void aud_PlayMusic(Music* mus, int loop);
void aud_StopMusic();

void aud_PauseMusic();
void aud_ResumeMusic();

Sound* aud_LoadSound(char* fname);
void aud_FreeSound(Sound* snd);

void aud_PlaySound(int chan, Sound* snd, int loop);

/*
#include <string>

class Sound
{
public:
	Sound();
	Sound(std::string fname);
	~Sound();

	void play();

private:
	void* data;

};

class Music
{
public:
	Music();
	Music(std::string fname);
	~Music();

	void play(bool loop = true);
	void stop();

	void pause();
	void resume();

private:
	void* data;

};

*/