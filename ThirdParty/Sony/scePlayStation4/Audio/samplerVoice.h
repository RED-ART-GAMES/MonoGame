#pragma once

#include "predecls.h"
#include <ngs2.h>

namespace Audio {

class AudioBuffer;

// This enum mirrors the one in XNA
enum class SoundState
{
    Playing,
    Paused,
    Stopped
};

class CS_API SamplerVoice
{
	friend class SoundSystem;

protected:

	CS_IGNORE SceNgs2Handle _rackHandle;

	CS_IGNORE SceNgs2Handle _voiceHandle;
	CS_IGNORE unsigned int _voiceHandleID;
	CS_IGNORE float _pitch;
	CS_IGNORE float _pan;
	CS_IGNORE bool _padPort;
	CS_IGNORE float _volume;
	CS_IGNORE bool _looped;
	CS_IGNORE AudioBuffer *_buffer;


	CS_IGNORE void GetPanLevels(float angle, float *panLevels);
	CS_IGNORE void SetMatrixLevels(float *panLevels);

public:

	SamplerVoice(AudioBuffer *buffer);
	virtual ~SamplerVoice();

	void SetFade(float fadeinTime, float fadeOutTime);

	SoundState GetState();

	float GetVolume();
	void SetVolume(float newVol);
	
	bool GetLooped();
	void SetLooped(bool loop);

	void SetPan(float pan);
	float GetPan();

	void SetPitch(float pitch);
	float GetPitch();

};

} // namespace Audio
