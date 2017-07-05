#pragma once

#include <gslib.h>
#include "IntVector2.h"
class VectorUtil
{
public:
	VectorUtil()=default;
	~VectorUtil()=default;

	static IntVector2 vec2toiVec2(const GSvector2& _v);
	//z–³Ž‹
	static IntVector2 vec2toiVec3(const GSvector3& _v);

	static GSvector2 iVec2tovec2(const IntVector2& _v);
	//z==0
	static GSvector3 iVec2tovec3(const IntVector2 & _v);

	static bool nearlyEqual(const GSvector3& _v1, const GSvector3& _v2, float _epsilon);

};
