#pragma once
/**
* @file LookAtDesc.h
* @brief LookAtãLèqéq
* @author èºîˆóTñÁ
* @date 2016/3/2
*/
#include <gslib.h>
struct LookAtDesc
{
	LookAtDesc()
		:eye(0.0f, 0.0f,40.0f),
		at(0.0f, 0.0f, 0.0f),
		up(0.0f, 1.0f, 0.0f)
	{}

	GSvector3 eye;
	GSvector3 at;
	GSvector3 up;
};