#pragma once

#include "predecls.h"

namespace Input {

class CS_API Mouse
{
	Mouse() {}

public:
	CS_IGNORE static void Initialize();
	CS_IGNORE static void Terminate();
	CS_IGNORE static void Update();

	CS_IGNORE static int Enable(SceUserServiceUserId userId, int playerIndex);
	CS_IGNORE static int Disable(int playerIndex);

	static bool GetState(
		int playerIndex,
		CS_OUT int &packetNumber,
		CS_OUT uint32_t &buttons,
		CS_OUT int32_t &xAxis,
		CS_OUT int32_t &yAxis,
		CS_OUT int32_t &wheel,
		CS_OUT int32_t &tilt);
};

} // namespace Input
