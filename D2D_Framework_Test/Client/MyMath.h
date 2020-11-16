#pragma once
#include <random>

class CMyMath
{
public:
	static float_t fRand(std::pair<float, float> range);
	static int32_t Rand(std::pair<int32_t, int32_t> range);

};