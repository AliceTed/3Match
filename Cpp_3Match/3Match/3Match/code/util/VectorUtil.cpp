#include "VectorUtil.h"

IntVector2 VectorUtil::vec2toiVec2(const GSvector2 & _v)
{
	return IntVector2(_v.x,_v.y);
}

IntVector2 VectorUtil::vec2toiVec3(const GSvector3 & _v)
{
	return IntVector2(_v.x, _v.y);
}

GSvector2 VectorUtil::iVec2tovec2(const IntVector2 & _v)
{
	return GSvector2(_v.x,_v.y);
}

GSvector3 VectorUtil::iVec2tovec3(const IntVector2 & _v)
{
	return GSvector3(_v.x, _v.y,0.0f);
}

bool VectorUtil::nearlyEqual(const GSvector3 & _v1, const GSvector3 & _v2, float _epsilon)
{
	const GSvector3 remainder = _v1 - _v2;
	if (remainder.x > _epsilon)return false;
	if (remainder.x < -_epsilon)return false;
	if (remainder.y > _epsilon)return false;
	if (remainder.y < -_epsilon)return false;
	if (remainder.z > _epsilon)return false;
	if (remainder.z < -_epsilon)return false;
	return true;;
}
