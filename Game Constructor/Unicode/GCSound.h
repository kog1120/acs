#pragma once

#include "GCInclude.h"

#pragma once

#include "fmodinc/fmod.h"
#include <stdio.h>

#pragma comment(lib, "fmodvc.lib")

class CGCSound {
private:	// Sound
	FSOUND_STREAM* m_stream;
	int            m_channel;

public:
	void InitSound();
	void LoadSound(char* file) { m_stream = FSOUND_Stream_Open(file, FSOUND_NORMAL, 0, 0); }
	void Play(int volume);
	void Stop() { if(m_stream != NULL) FSOUND_Stream_Stop(m_stream); }
};