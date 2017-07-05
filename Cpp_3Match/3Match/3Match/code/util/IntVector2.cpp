#include "IntVector2.h"
#include <cassert>
const IntVector2 IntVector2::ZERO=IntVector2();
const IntVector2 IntVector2::ONE=IntVector2(1,1);


IntVector2::IntVector2()
	:x(0),y(0)
{
}

IntVector2::IntVector2(int _x, int _y)
	:x(_x),y(_y)
{
}

IntVector2 IntVector2::inverse()
{
	return IntVector2(y,x);
}

IntVector2 & IntVector2::operator+()
{
	return *this;
}

IntVector2 IntVector2::operator-() 
{
	return IntVector2(-x, -y);
}

IntVector2 & IntVector2::operator+=(const IntVector2 & v)
{
	x += v.x;
	y += v.y;
	return *this;
}

IntVector2 & IntVector2::operator-=(const IntVector2 & v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

IntVector2 & IntVector2::operator*=(int i)
{
	x *= i;
	y *= i;
	return *this;
}

IntVector2 & IntVector2::operator/=(const IntVector2 & v)
{
	assert(v.y == 0|| v.x == 0);
	x /= v.x;
	y /= v.y;
	return *this;
}

IntVector2 & IntVector2::operator/=(int i)
{
	if (i == 0)
	{
		x = i;
		y = i;
		return *this;
	}
	x /= i;
	y /= i;
	return *this;
}

bool IntVector2::operator==(const IntVector2 & v)
{
	return x == v.x&&y == v.y;
}

bool IntVector2::operator!=(const IntVector2 & v)
{
	return !(*this == v);
}


IntVector2 operator+(const IntVector2 & v1, const IntVector2 & v2)
{
	IntVector2 tmp(v1);
	return tmp += v2;
}

IntVector2 operator-(const IntVector2 & v1, const IntVector2 & v2)
{
	IntVector2 tmp(v1);
	return tmp -= v2;
}

IntVector2 operator*(const IntVector2 & v, int i)
{
	IntVector2 tmp(v);
	return tmp *= i;
}

IntVector2 operator/(const IntVector2 & v, int i)
{
	IntVector2 tmp(v);
	return tmp /= i;
}

IntVector2 operator/(int i, const IntVector2 & v)
{
	assert(v.y==0);
	assert(v.x == 0);
	return IntVector2(i / v.x, i / v.y);
}
