#pragma once
#include "predecls.h"

#include <scebase.h>
#include <rtc.h>

namespace System {


enum class RtcResult
{
	Ok = SCE_OK,

	ErrorNotInitialized = SCE_RTC_ERROR_NOT_INITIALIZED,
	ErrorInvalidPointer = SCE_RTC_ERROR_INVALID_POINTER,
	ErrorInvalidValue = SCE_RTC_ERROR_INVALID_VALUE,
	ErrorInvalidArg = SCE_RTC_ERROR_INVALID_ARG,
	ErrorNotSupported = SCE_RTC_ERROR_NOT_SUPPORTED,
	ErrorNoClock = SCE_RTC_ERROR_NO_CLOCK,
	ErrorBadParse = SCE_RTC_ERROR_BAD_PARSE,
	ErrorInvalidYear = SCE_RTC_ERROR_INVALID_YEAR,
	ErrorInvalidMonth = SCE_RTC_ERROR_INVALID_MONTH,
	ErrorInvalidDay = SCE_RTC_ERROR_INVALID_DAY,
	ErrorInvalidHour = SCE_RTC_ERROR_INVALID_HOUR,
	ErrorInvalidMinute = SCE_RTC_ERROR_INVALID_MINUTE,
	ErrorInvalidSecond = SCE_RTC_ERROR_INVALID_SECOND,
	ErrorInvalidMicrosecond = SCE_RTC_ERROR_INVALID_MICROSECOND,
};


class CS_API Rtc
{
	Rtc() {}

public:

	static RtcResult GetCurrentNetworkTick(CS_OUT uint64_t* tick);

	static RtcResult GetCurrentNetworkTimeT(CS_OUT int64_t* time_t);

};

} // namespace System
