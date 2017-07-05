#pragma once
/**
* @file MeshRenderDesc.h
* @brief メッシュ描画記述子
* @author 松尾裕也
* @date 2016/3/2
*/
#include <gslib.h>
struct MeshRenderDesc
{
	MeshRenderDesc()
		:meshID(0),
		color(1.0f,1.0f,1.0f,1.0f)
	{
		matrix.identity();
	}
	unsigned int meshID;
	GSmatrix4 matrix;
	GScolor color;
};