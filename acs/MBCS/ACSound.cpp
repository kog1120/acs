#include "ACInclude.h"
#include "../fmodinc/fmod.h"
#include "ACSound.h"

void GCSound::InitSound()
{
	FSOUND_Init(44100, 64, 0);
	FSOUND_DSP_SetActive(FSOUND_DSP_GetFFTUnit(), true);
}

void GCSound::Play(int volume)
{
	_channel = FSOUND_Stream_Play(FSOUND_FREE, _stream);
	FSOUND_SetVolume(_channel, volume);
	FSOUND_SetLoopMode(_channel, FSOUND_LOOP_NORMAL);
}