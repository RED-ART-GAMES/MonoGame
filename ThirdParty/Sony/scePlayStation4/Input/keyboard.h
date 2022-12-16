#pragma once

#include "predecls.h"

namespace Input {

class CS_API Keyboard
{
	Keyboard() { }

public:
	CS_IGNORE static void Initialize();
	CS_IGNORE static void Terminate();
	CS_IGNORE static void Update();

	CS_IGNORE static int Enable(SceUserServiceUserId userId, int playerIndex);
	CS_IGNORE static int Disable(int playerIndex);

	static void GetState(int playerIndex, 
		CS_OUT uint32_t &keys0, 
		CS_OUT uint32_t &keys1, 
		CS_OUT uint32_t &keys2, 
		CS_OUT uint32_t &keys3, 
		CS_OUT uint32_t &keys4, 
		CS_OUT uint32_t &keys5, 
		CS_OUT uint32_t &keys6, 
		CS_OUT uint32_t &keys7);
};

} // namespace Input
