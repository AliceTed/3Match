#include "Math.h"
#include <random>
int Math::random(int _min, int _max)
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> range(_min, _max);
	return range(mt);
}

float Math::random(float _min, float _max)
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_real_distribution<> range(_min, _max);
	return static_cast<float>(range(mt));
}
