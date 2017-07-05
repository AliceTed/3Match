#pragma once
#include <cmath>
class Math
{
public:
	template<class T>
	static T wrap(const T& _x, const T& _low, const T& _hight);
	template<class T>
	static T clamp(const T& _x, const T& _min, const T& _max);


	static int random(int _min, int _max);
	static float random(float _min, float _max);
};

template<class T>
inline T Math::wrap(const T & _x, const T & _low, const T & _hight)
{
	const T n = std::fmod(_x - _low, _hight - _low);
	return (n >= 0) ? (n + _low) : (n + _hight);
}

template<class T>
inline T Math::clamp(const T & _x, const T & _min, const T & _max)
{
	return std::fmax(_min, std::fmin(_x, _max));
}
