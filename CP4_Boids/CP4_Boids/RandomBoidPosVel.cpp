#include "RandomBoidPosVel.h"

std::default_random_engine RandomBoidPosVel::generator;
std::uniform_int_distribution<int> RandomBoidPosVel::velDistribution(0, 0);
std::uniform_int_distribution<int> RandomBoidPosVel::posDistribution(0, 0);

void RandomBoidPosVel::InitVel(int min, int max)
{
	std::uniform_int_distribution<int> distr(min, max);
	velDistribution = distr;
}

void RandomBoidPosVel::InitPos(int min, int max)
{
	std::uniform_int_distribution<int> distr(min, max);
	posDistribution = distr;
}

int RandomBoidPosVel::GetVelocityComp()
{
	int randVal = velDistribution(generator);
	if (randVal == 0)
		return 1;
	else
		return randVal;
}

int RandomBoidPosVel::GetPositionComp()
{
	return posDistribution(generator);
}
