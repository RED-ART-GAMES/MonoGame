#pragma once

struct VideoShaderConstants
{
	float pos_top;
	float pos_left;
	float pos_right;
	float pos_bottom;

	float tex_top;
	float tex_left;
	float tex_right;
	float tex_bottom;
};

static const unsigned video_p_pssl_sb[] = {
	#include "..\video_p.h"
};
static const unsigned video_vv_pssl_sb[] = {
	#include "..\video_vv.h"
};
