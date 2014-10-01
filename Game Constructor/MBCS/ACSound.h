#pragma once

#pragma comment(lib, "fmodvc.lib")

class GCSound 
{
public:
	void InitSound();
	void LoadSound(char* file) { _stream = FSOUND_Stream_Open(file, FSOUND_NORMAL, 0, 0); }
	void Play(int volume);
	void Stop() { if(_stream != NULL) FSOUND_Stream_Stop(_stream); }

private:	// Sound
	FSOUND_STREAM* _stream;
	int            _channel;
};