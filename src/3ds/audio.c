#include "audio.h"
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum AudioMode { NONE = 0, CSND, NDSP };

static enum AudioMode audioMode = NONE;

#define NDSP_NUM_CHANNELS 24
ndspWaveBuf waveBuf[NDSP_NUM_CHANNELS];

void aud_Init()
{
	//Try to use NDSP
	if (!ndspInit())
	{
		//printf("\nNDSP Sucess");

		audioMode = NDSP;
		ndspSetOutputMode(NDSP_OUTPUT_MONO);
		ndspSetOutputCount(1);
	}

	//Fall back to CSND
	else
	{
		//printf("\nNDSP Failed");

		if (!csndInit())
		{
			//printf("\nCSND Sucess");

			audioMode = CSND;
		}

		//Give up. Sound won't work.
		else
		{
			//printf("\nCSND Failed\nNo sound will play.");
		}
	}
}

void aud_Exit()
{
	aud_StopMusic();
	
	if (audioMode == NDSP)
		ndspExit();

	if (audioMode == CSND)
		csndExit();
	
	audioMode = NONE;
}

Music* aud_LoadMusic(char* fname)
{
	return aud_LoadSound(fname);
}

void aud_FreeMusic(Music* mus)
{
	linearFree(mus->data);
	mus->data = NULL;

	free(mus);
	mus = NULL;
}

void aud_PlayMusic(Music* mus, int loop)
{
	aud_PlaySound(0, mus, loop);
}

void aud_StopMusic()
{
	if (audioMode == NDSP)
		ndspChnWaveBufClear(0);

	else if (audioMode == CSND)
	{
		CSND_UpdateInfo(0);
		CSND_SetPlayState(8, 0);
		CSND_UpdateInfo(0);
	}
}

void aud_PauseMusic()
{
	if (audioMode == NDSP)
		ndspChnSetPaused(0, true);

	else if (audioMode == CSND)
	{
		CSND_UpdateInfo(0);
		CSND_SetPlayState(8, 0);
		CSND_UpdateInfo(0);
	}
}

void aud_ResumeMusic()
{
	if (audioMode == NDSP)
		ndspChnSetPaused(0, false);

	else if (audioMode == CSND)
	{
		CSND_UpdateInfo(0);
		CSND_SetPlayState(8, 1);
		CSND_UpdateInfo(0);
	}
}

Sound* aud_LoadSound(char* fname)
{		
	Sound* snd = NULL;
	FILE* f;

	char fullpath[256];
	strcpy(fullpath, "romfs:");
	strcat(fullpath, fname);

	if ( (f = fopen(fullpath, "rb")) )
	{
		#pragma pack(push,1)
		typedef struct
		{
			u32 ChunkID;
			u32 ChunkSize;
			u32 Format;
			u32 Subchunk1ID;
			u32 Subchunk1Size;
			u16 AudioFormat;
			u16 NumChannels;
			u32 SampleRate;
			u32 ByteRate;
			u16 BlockAlign;
			u16 BitsPerSample;
			u32 Subchunk2ID;
			u32 Subchunk2Size;
		} WAVHeader;
		#pragma pack(push,0)

		//Read Wav header
		WAVHeader wh;
		fread(&wh, 1, sizeof(WAVHeader), f);

		//Header validation
		if (wh.ChunkID == 0x46464952 &&
			wh.Subchunk1ID == 0x20746d66)
		{
			//'fact' block, want data
			if (wh.Subchunk2ID == 0x74636166)
			{
				fseek(f, 0x30, SEEK_SET);
				fread(&wh.Subchunk2ID, 1, sizeof(u32), f);
				fread(&wh.Subchunk2Size, 1, sizeof(u32), f);
			}

			snd = (Sound*)malloc(sizeof(Sound));

			snd->sampleRate = (float)wh.SampleRate;
			snd->bitsPerSample = wh.BitsPerSample;
			snd->size = wh.Subchunk2Size;
			snd->numChannels = wh.NumChannels;
			
			snd->data = (u8*)linearAlloc(snd->size);
			fread(snd->data, 1, snd->size, f);
			
			//Convert 8-bit unsigned to 8-bit signed
			if (snd->bitsPerSample == 8)
				for (long i = 0; i < snd->size; i++)
					snd->data[i] -= 128;
		}
	}

	fclose(f);
	return snd;
}

void aud_FreeSound(Sound* snd)
{
	aud_FreeMusic(snd);
}

void aud_PlaySound(int chan, Sound* snd, int loop)
{
	if (snd != NULL)
	{
		//NDSP
		if (audioMode == NDSP)
		{
			//Get first free channel
			if (chan == -1)
			{
				for (chan = 1; chan < NDSP_NUM_CHANNELS; chan++)
				{
					if (ndspChnIsPlaying(chan) == false)
						break;
				}
			}

			//Get format
			u16 ndspFormat = 0;

			if (snd->bitsPerSample == 8)
			{
				ndspFormat = (snd->numChannels == 1)?
					NDSP_FORMAT_MONO_PCM8 :
					NDSP_FORMAT_STEREO_PCM8;
			}
			else if (snd->bitsPerSample == 16)
			{
				ndspFormat = (snd->numChannels == 1)?
					NDSP_FORMAT_MONO_PCM16 :
					NDSP_FORMAT_STEREO_PCM16;
			}

			ndspChnReset(chan);
			ndspChnSetInterp(chan, NDSP_INTERP_NONE);
			ndspChnSetRate(chan, (float)snd->sampleRate);
			ndspChnSetFormat(chan, ndspFormat);
			
			memset(&waveBuf[chan], 0, sizeof(ndspWaveBuf));
			waveBuf[chan].data_vaddr = (u32*)snd->data;		
			waveBuf[chan].nsamples = snd->size / (snd->bitsPerSample >> 3) / snd->numChannels;
			waveBuf[chan].looping = (loop == 0)?false : true;
			waveBuf[chan].status = NDSP_WBUF_PLAYING;

			DSP_FlushDataCache(snd->data, snd->size);
			ndspChnWaveBufAdd(chan, &waveBuf[chan]);
		}

		//CSND
		else if (audioMode == CSND)
		{
			//Search for first unused channel
			if (chan == -1)
			{
				u8 isPlaying;
				for (int i = 1; i < CSND_NUM_CHANNELS; i++)
				{
					chan = (i + 1) * 8;
					csndIsPlaying(chan, &isPlaying);

					if (isPlaying == 0)
						break;
				}
			}
			else
			{
				chan = (chan + 1) * 8;
			}
			
			//printf("\nChannel %d", chan);
			
			//Flags
			u32 flags = 0;

			if (loop == 0)
				flags = flags | SOUND_ONE_SHOT;
			else
				flags = flags | SOUND_REPEAT;

			//Set sound format
			if (snd->bitsPerSample == 8)
				flags = flags | SOUND_FORMAT_8BIT;

			else if (snd->bitsPerSample == 16)
				flags = flags | SOUND_FORMAT_16BIT;
			
			csndPlaySound(chan, flags, snd->sampleRate, 1.0f, 0.0f, snd->data, snd->data, snd->size);
			
			//CSND is dumb and needs persuasion to continue its play state
			CSND_UpdateInfo(1);
			CSND_SetPlayState(chan, 1);
			CSND_UpdateInfo(1);
			
			CSND_UpdateInfo(1);
			CSND_SetPlayState(chan, 1);
			CSND_UpdateInfo(1);
			
			CSND_UpdateInfo(1);
			CSND_SetPlayState(chan, 1);
			CSND_UpdateInfo(1);
			
			CSND_UpdateInfo(1);
			CSND_SetPlayState(chan, 1);
			CSND_UpdateInfo(1);
		}
	}
}