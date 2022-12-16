#include "videoPlayer.h"
#include "audio_output.h"
#include "../allocator.h"
#include "../Graphics/graphicsSystem.h"

#include <assert.h>
#include <memory>
#include <libsysmodule.h>
#include <sceerror.h>
#include <gnm.h>
#include <sceavplayer_ex.h>
#include <video_out.h>
#include <audioout.h>

using namespace sce;
using namespace Graphics;
using namespace Media;

namespace {

	void* videoAlloc(void* argP, uint32_t argAlignment, uint32_t argSize) { return mem::alloc(argSize, argAlignment); }
	void videoFree(void* argP, void* argMemory) { mem::free(argMemory); }
	void* videoAllocTexture(void* argP, uint32_t argAlignment, uint32_t argSize) { return mem::alloc(argSize, argAlignment); }
	void videoFreeTexture(void* argP, void* argMemory) { mem::free(argMemory); }

	void* audioOutputThread(void* arg)
	{
		auto player = (VideoPlayer*)arg;
		assert(player != nullptr);

		const uint32_t outputStreamGrain = 1024;
		AudioOutput output;
		output.open(outputStreamGrain, 48000, SCE_AUDIO_OUT_PARAM_FORMAT_S16_STEREO);

		void* silence = mem::alloc(4096, 0x20);
		memset(silence, 0, 4096);

		SceAvPlayerFrameInfo audioFrame;
		memset(&audioFrame, 0, sizeof(SceAvPlayerFrameInfo));

		while (sceAvPlayerIsActive(player->_handle))
		{
			scePthreadMutexLock(&player->_audioMutex);
			float volume = player->_volume;
			auto isMuted = player->_isMuted || volume < 0.001f;
			scePthreadMutexUnlock(&player->_audioMutex);

			if (output.getVolume() != volume)
				output.setVolume(volume);

			if (sceAvPlayerGetAudioData(player->_handle, &audioFrame) && !isMuted)
				output.output(audioFrame.pData);
			else
				output.output(silence);
		}

		output.close();
		mem::free(silence);

		scePthreadExit(nullptr);
		return nullptr;
	}
}

VideoPlayer::VideoPlayer(GraphicsSystem* graphics)
{
	auto ret = sceSysmoduleLoadModule(SCE_SYSMODULE_VIDEODEC);
	assert(ret == SCE_OK);
	ret = sceSysmoduleLoadModule(SCE_SYSMODULE_AV_PLAYER);
	assert(ret == SCE_OK);

	scePthreadMutexInit(&_audioMutex, NULL, "av_audio_mutex");

	SceAvPlayerInitData param;
	memset(&param, 0, sizeof(SceAvPlayerInitData));
	param.memoryReplacement.objectPointer = NULL;
	param.memoryReplacement.allocate = videoAlloc;
	param.memoryReplacement.deallocate = videoFree;
	param.memoryReplacement.allocateTexture = videoAllocTexture;
	param.memoryReplacement.deallocateTexture = videoFreeTexture;

#ifdef	_DEBUG
	param.debugLevel = SCE_AVPLAYER_DBG_ALL; // SCE_AVPLAYER_DBG_WARNINGS;
#else
	param.debugLevel = SCE_AVPLAYER_DBG_INFO;
#endif
	
	param.basePriority = 700;
	param.numOutputVideoFrameBuffers = 6;
	param.autoStart = true;
	param.defaultLanguage = "eng";

	_state = VideoPlayerState::Not_Loaded;
	_handle = sceAvPlayerInit(&param);
	_graphics = graphics;
	_sourceID = -1;
	_volume = 1.0f;
	_isMuted = false;
	_isLooped = false;
}

VideoPlayer::~VideoPlayer()
{
	sceAvPlayerStop(_handle);
	scePthreadJoin(_audioThread, NULL);

	scePthreadMutexDestroy(&_audioMutex);

	sceAvPlayerClose(_handle);
	_handle = nullptr;
	_sourceID = -1;
	_state = VideoPlayerState::Not_Loaded;
}

bool VideoPlayer::GrabFrame()
{
	if (!sceAvPlayerIsActive(_handle))
	{
		_state = VideoPlayerState::Stopped;
		return false;
	}

	SceAvPlayerFrameInfoEx videoFrame;
	memset(&videoFrame, 0, sizeof(SceAvPlayerFrameInfoEx));
	if(!sceAvPlayerGetVideoDataEx(_handle, &videoFrame))
		return false;

	if (videoFrame.pData == nullptr)
		return false;


	void* lumaAddress;
	void* chromaAddress;
	Gnm::Texture lumaTexture;
	Gnm::Texture chromaTexture;

	//auto frameWidth = videoFrame.details.video.width;
	auto frameHeight = videoFrame.details.video.height;
	auto framePitch = videoFrame.details.video.pitch;

	// Setup luma texture.
	{
		Gnm::SizeAlign sz;

#if SCE_ORBIS_SDK_VERSION >= 0x05008041u // SDK Version 5.0

		Gnm::TextureSpec spec;
		spec.init();
		spec.m_textureType = Gnm::TextureType::kTextureType2d;
		spec.m_format = Gnm::kDataFormatR8Unorm;
		spec.m_width = framePitch;
		spec.m_height = frameHeight;
		spec.m_depth = 1;
		spec.m_numMipLevels = 1;
		spec.m_tileModeHint = Gnm::kTileModeDisplay_LinearAligned;
		spec.m_numFragments = Gnm::kNumFragments1;
		spec.m_minGpuMode = Gnm::getGpuMode();
		spec.m_numSlices = 1;
		spec.m_pitch = 0;

		auto err = lumaTexture.init(&spec);
		SCE_GNM_ASSERT(err == SCE_GNM_OK);
		sz = lumaTexture.getSizeAlign();
#else
		sz = lumaTexture.initAs2d(framePitch, frameHeight, 1, Gnm::kDataFormatR8Unorm, Gnm::kTileModeDisplay_LinearAligned,
#if SCE_ORBIS_SDK_VERSION >= 0x02000071u // SDK Version 2.0
			Gnm::kNumFragments1);
#else
			Gnm::kNumSamples1);
#endif
#endif

		assert(sz.m_size == framePitch * frameHeight);
		lumaAddress = videoFrame.pData;
		lumaTexture.setBaseAddress256ByteBlocks((uint32_t)(reinterpret_cast<uint64_t>(lumaAddress) >> 8));
	}

	// Setup chroma texture.
	{
		Gnm::SizeAlign sz;

#if SCE_ORBIS_SDK_VERSION >= 0x05008041u // SDK Version 5.0

		Gnm::TextureSpec spec;
		spec.init();
		spec.m_textureType = Gnm::TextureType::kTextureType2d;
		spec.m_format = Gnm::kDataFormatR8G8Unorm;
		spec.m_width = framePitch / 2;
		spec.m_height = frameHeight / 2;
		spec.m_depth = 1;
		spec.m_numMipLevels = 1;
		spec.m_tileModeHint = Gnm::kTileModeDisplay_LinearAligned;
		spec.m_numFragments = Gnm::kNumFragments1;
		spec.m_minGpuMode = Gnm::getGpuMode();
		spec.m_numSlices = 1;
		spec.m_pitch = 0;

		auto err = chromaTexture.init(&spec);
		SCE_GNM_ASSERT(err == SCE_GNM_OK);
		sz = chromaTexture.getSizeAlign();
#else
		sz = chromaTexture.initAs2d(framePitch / 2, frameHeight / 2, 1, Gnm::kDataFormatR8G8Unorm, Gnm::kTileModeDisplay_LinearAligned,
#if SCE_ORBIS_SDK_VERSION >= 0x02000071u // SDK Version 2.0
			Gnm::kNumFragments1);
#else
			Gnm::kNumSamples1);
#endif		
#endif

		assert(sz.m_size == framePitch * (frameHeight / 2));
		chromaAddress = (uint8_t*)(videoFrame.pData) + (framePitch * frameHeight);
		chromaTexture.setBaseAddress256ByteBlocks((uint32_t)(reinterpret_cast<uint64_t>(chromaAddress) >> 8));
	}

	// Draw
	auto left = (framePitch > 0) ? ((float)videoFrame.details.video.cropLeftOffset / framePitch) : 0.0f;
	auto right = (framePitch > 0) ? 1.0f - ((float)videoFrame.details.video.cropRightOffset / framePitch) : 1.0f;
	auto top = (frameHeight > 0) ? ((float)videoFrame.details.video.cropTopOffset / frameHeight) : 0.0f;
	auto bottom = (frameHeight > 0) ? 1.0f - ((float)videoFrame.details.video.cropBottomOffset / frameHeight) : 1.0f;
	_graphics->DrawYCbCr(&lumaTexture, &chromaTexture, left, right, top, bottom);

	return true;
}

void VideoPlayer::Pause()
{
	if (_state != VideoPlayerState::Playing)
		return;

	auto ret = sceAvPlayerPause(_handle);
	assert(ret == SCE_OK);
	if (ret == SCE_OK)
		_state = VideoPlayerState::Paused;
}

void VideoPlayer::Resume()
{
	if (_state != VideoPlayerState::Paused)
		return;

	auto ret = sceAvPlayerResume(_handle);
	assert(ret == SCE_OK);
	if (ret == SCE_OK)
		_state = VideoPlayerState::Playing;
}

void VideoPlayer::Play(const char* filename)
{
    switch(_state)
	{
	case VideoPlayerState::Loaded:
	case VideoPlayerState::Paused:
		return;

	case VideoPlayerState::Not_Loaded:
		{
			_sourceID = sceAvPlayerAddSource(_handle, filename);
			sceAvPlayerSetLooping(_handle, _isLooped);

			ScePthreadAttr threadAttr;
			scePthreadAttrInit(&threadAttr);
			scePthreadAttrSetstacksize(&threadAttr, 1024 * 1024);
			scePthreadAttrSetaffinity(&threadAttr, (1 << 4) | (1 << 5));
			auto ret = scePthreadCreate(&_audioThread, &threadAttr, audioOutputThread, this, "av_audio_output_thread");
			scePthreadAttrDestroy(&threadAttr);
			if (ret < 0)
			{
				printf("Couldn't start audio thread: 0x%08X\n", ret);
				return;
			}

			_state = VideoPlayerState::Playing;
		}
		break;

	case VideoPlayerState::Playing:
		sceAvPlayerJumpToTime(_handle, 0);
		return;

	case VideoPlayerState::Stopped:
		sceAvPlayerResume(_handle);
		sceAvPlayerJumpToTime(_handle, 0);
		_state = VideoPlayerState::Playing;
		break;
	}
}

void VideoPlayer::Stop()
{
	if (_state == VideoPlayerState::Stopped)
		return;

	if (_state != VideoPlayerState::Playing && _state != VideoPlayerState::Paused)
		return;

	// If already paused, we cannot call sceAvPlayerPause again, so
	// we just mark the state as stopped and return.
	if (_state == VideoPlayerState::Paused)
	{
		_state = VideoPlayerState::Stopped;
		return;
	} else {
		auto ret = sceAvPlayerPause(_handle);
		assert(ret == SCE_OK);
		if (ret == SCE_OK)
			_state = VideoPlayerState::Stopped;
	}
}

void VideoPlayer::SetVolume(float volume)
{
	scePthreadMutexLock(&_audioMutex);
	_volume = volume;
	scePthreadMutexUnlock(&_audioMutex);
}

time_t VideoPlayer::GetPlayPosition()
{
	return sceAvPlayerCurrentTime(_handle);
}

void VideoPlayer::SetIsLooped(bool value)
{
	_isLooped = value;

	if (_state != VideoPlayerState::Not_Loaded)
	{
		auto ret = sceAvPlayerSetLooping(_handle, value);
		assert(ret == SCE_OK);
	}
}

void VideoPlayer::SetIsMuted(bool value)
{
	scePthreadMutexLock(&_audioMutex);
	_isMuted = value;
	scePthreadMutexUnlock(&_audioMutex);
}
