#pragma once

#define CS_IGNORE
#define CS_OUT
#define CS_IN_OUT
#define CS_VALUE_TYPE
#define CS_FLAGS

#if !defined(CS_BINDING_GEN)
#define CS_API __declspec(dllexport)
#else
#undef __cplusplus
#define __cplusplus	 201104L
#define CS_API
#endif

#include <stdint.h>

typedef int32_t UserServiceUserId;
