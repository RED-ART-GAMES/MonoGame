#include "systemService.h"

#include <sdk_version.h>
#include <kernel.h>
#include <memory.h>
#include <assert.h>

using namespace System;


SystemLang SystemService::GetLanguage()
{
	int32_t language;
	auto result = sceSystemServiceParamGetInt(SCE_SYSTEM_SERVICE_PARAM_ID_LANG, &language);
	assert(result == SCE_OK);
	return (SystemLang)language;
}

SystemDateFormat SystemService::GetDateFormat()
{
	int32_t format;
	auto result = sceSystemServiceParamGetInt(SCE_SYSTEM_SERVICE_PARAM_ID_DATE_FORMAT, &format);
	assert(result == SCE_OK);
	return (SystemDateFormat)format;
}

SystemTimeFormat SystemService::GetTimeFormat()
{
	int32_t format;
	auto result = sceSystemServiceParamGetInt(SCE_SYSTEM_SERVICE_PARAM_ID_TIME_FORMAT, &format);
	assert(result == SCE_OK);
	return (SystemTimeFormat)format;
}

int32_t SystemService::GetTimeZoneOffset()
{
	int32_t offset;
	auto result = sceSystemServiceParamGetInt(SCE_SYSTEM_SERVICE_PARAM_ID_TIME_ZONE, &offset);
	assert(result == SCE_OK);
	return offset;
}

bool SystemService::GetIsDaylightSavingsTime()
{
	int32_t summertime;
	auto result = sceSystemServiceParamGetInt(SCE_SYSTEM_SERVICE_PARAM_ID_SUMMERTIME, &summertime);
	assert(result == SCE_OK);
	return summertime > 0 ? true : false;
}

SystemServiceResult SystemService::LoadExec(const char *path, char* const argv[])
{
	auto result = sceSystemServiceLoadExec(path, argv);
	return (SystemServiceResult)result;
}

void SystemService::HideSplashScreen()
{
	auto result = sceSystemServiceHideSplashScreen();
	assert(result == SCE_OK);
}

void SystemService::DisableMusicPlayer()
{
	auto result = sceSystemServiceDisableMusicPlayer();
	assert(result == SCE_OK);
}

void SystemService::ReenableMusicPlayer()
{
	auto result = sceSystemServiceReenableMusicPlayer();
	assert(result == SCE_OK);
}

SystemServiceResult SystemService::GetDisplaySafeAreaInfo(CS_OUT float *ratio)
{
	SceSystemServiceDisplaySafeAreaInfo info;
	memset(&info, 0, sizeof(info));
	auto result = sceSystemServiceGetDisplaySafeAreaInfo(&info);
	if (result == SCE_OK)
		*ratio = info.ratio;

	return (SystemServiceResult)result;
}

int32_t SystemService::GetNumRecieveEvents()
{
	SceSystemServiceStatus status;
	sceSystemServiceGetStatus(&status);
	return status.eventNum;
}

bool SystemService::ReceiveEvent(CS_OUT SystemServiceEvent *eventType)
{
	SceSystemServiceEvent event;
	auto result = sceSystemServiceReceiveEvent(&event);
	if (result != SCE_OK)
		return false;

	*eventType = (SystemServiceEvent)event.eventType;
	// TODO: Return data too!

	return true;
}

bool SystemService::GetIsSystemUIOverlaid()
{
	SceSystemServiceStatus status;
	sceSystemServiceGetStatus(&status);
	return status.isSystemUiOverlaid;
}

bool SystemService::GetIsInBackgroundExecution()
{
	SceSystemServiceStatus status;
	sceSystemServiceGetStatus(&status);
	return status.isInBackgroundExecution;
}

GpuLoadEmulationMode SystemService::GetGpuLoadEmulationMode()
{
	auto result = sceSystemServiceGetGpuLoadEmulationMode();
	return (GpuLoadEmulationMode)result;
}

void SystemService::SetGpuLoadEmulationMode(GpuLoadEmulationMode mode)
{
	auto result = sceSystemServiceSetGpuLoadEmulationMode((SceSystemServiceGpuLoadEmulationMode)mode);
	assert(result == SCE_OK);
}

SystemServiceRenderingMode SystemService::GetRenderingMode()
{
#if SCE_ORBIS_SDK_VERSION >= 0x04008081u
	return SystemServiceRenderingMode::Base;
#elif SCE_ORBIS_SDK_VERSION >= 0x03508041u
	SceSystemServiceRenderingMode mode;
	auto result = sceSystemServiceGetRenderingMode(&mode);
	return (SystemServiceRenderingMode)mode;
#else
	return SystemServiceRenderingMode::Base;
#endif
}

bool SystemService::IsNeoMode()
{
#if SCE_ORBIS_SDK_VERSION >= 0x03508041u
	return sceKernelIsNeoMode() == 1;
#else
	return false;
#endif
}


