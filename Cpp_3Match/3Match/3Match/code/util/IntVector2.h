#pragma once

struct IntVector2
{
	int x;
	int y;

	IntVector2();
	IntVector2(int _x, int _y);

	IntVector2 inverse();

	IntVector2& operator +();
	IntVector2 operator -();
	IntVector2& operator +=(const IntVector2& v);
	IntVector2& operator -=(const IntVector2& v);
	IntVector2& operator *=(int i);
	IntVector2& operator /=(const IntVector2& v);
	IntVector2& operator /=(int i);
	bool operator ==(const IntVector2& v);
	bool operator !=(const IntVector2& v);

	static const IntVector2 ZERO;
	static const IntVector2 ONE;
};

 IntVector2 operator +(const IntVector2& v1, const IntVector2& v2);
 IntVector2 operator -(const IntVector2& v1, const IntVector2& v2);
 IntVector2 operator *(const IntVector2& v, int i);
 IntVector2 operator /(const IntVector2& v, int i);
 IntVector2 operator /(int i, const IntVector2& v);