#pragma once

/**
* @file SkyBoxRenderDesc.h
* @brief スカイボックス描画記述子
* @author 松尾裕也
* @date 2016/3/5
*/
struct SkyBoxRenderDesc
{
	SkyBoxRenderDesc()
		:meshID(0),
		time(0)
	{
	}
	unsigned int meshID;
	float time;
};