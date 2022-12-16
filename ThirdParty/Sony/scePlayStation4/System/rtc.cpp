#include "rtc.h"

#include <rtc.h>

#include <assert.h>
#include <libsysmodule.h>

using namespace System;

#pragma comment(lib, "libSceRtc_stub_weak.a")

RtcResult Rtc::GetCurrentNetworkTick(CS_OUT uint64_t* tick)
{
	*tick = 0;

	SceRtcTick rtcTick;
	int ret = sceRtcGetCurrentNetworkTick(&rtcTick);
	if (ret < 0)
		return (RtcResult)ret;

	*tick = rtcTick.tick;
	return RtcResult::Ok;
}

RtcResult Rtc::GetCurrentNetworkTimeT(CS_OUT int64_t* time_t_)
{
	*time_t_ = 0;

	SceRtcTick rtcTick;
	int ret = sceRtcGetCurrentNetworkTick(&rtcTick);
	if (ret < 0)
		return (RtcResult)ret;

	SceRtcDateTime time;
	ret = sceRtcSetTick(&time, &rtcTick);
	if (ret < 0)
		return (RtcResult)ret;

	time_t timet;
	ret = sceRtcGetTime_t(&time, &timet);
	if (ret < 0)
		return (RtcResult)ret;

	*time_t_ = timet;
	return RtcResult::Ok;
}
