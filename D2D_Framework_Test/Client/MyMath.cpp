#include "stdafx.h"
#include "MyMath.h"


float_t CMyMath::fRand(std::pair<float, float> range)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::uniform_real_distribution<float> dis(range.first, range.second);

	return dis(gen);
}

int32_t CMyMath::Rand(std::pair<int32_t, int32_t> range)
{
	return static_cast<int32_t>(std::round(CMyMath::fRand({ (float)range.first, (float)range.second })));
}
