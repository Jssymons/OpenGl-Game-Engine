#include "Random.h"

Random::Random()
{
	randomEngine.seed(std::time(nullptr));
}
void Random::Seed()
{
	randomEngine.seed(std::time(nullptr));
}

int64_t Random::IntInRange(int64_t low, int64_t high)
{
	std::uniform_int_distribution<int64_t> dist{ low, high };
	return dist(randomEngine);
}

float Random::FloatInRange(float low, float high)
{
	std::uniform_real_distribution<float> dist{ low, high };
	return dist(randomEngine);
}