#pragma once

#include "predecls.h"

namespace Input {

CS_IGNORE struct MouseState 
{
	bool IsConnected;
	int PacketNumber;

	uint32_t Buttons;
	int32_t  XAxis;
	int32_t  YAxis;
	int32_t  Wheel;
	int32_t  Tilt;
};

} // namespace Input
