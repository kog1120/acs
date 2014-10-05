#include "GCSound.h"

void CGCSound::InitSound()
{
	FSOUND_Init(44100, 64, 0);
	FSOUND_DSP_SetActive(FSOUND_DSP_GetFFTUnit(), true);
}

void CGCSound::Play(int volume)
{
	m_channel = FSOUND_Stream_Play(FSOUND_FREE, m_stream);
	FSOUND_SetVolume(m_channel, volume);
	FSOUND_SetLoopMode(m_channel, FSOUND_LOOP_NORMAL);
}