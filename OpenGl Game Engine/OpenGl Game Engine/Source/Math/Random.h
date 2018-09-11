#pragma once

#include <random>
#include <ctime>
#include <cstdint>

class Random
{
public:
	Random();
	void Seed();
	int64_t IntInRange(int64_t low, int64_t high);
	float FloatInRange(float low, float high);
private:
	std::mt19937_64 randomEngine;
};

