#pragma once

#include <random>

/**
*This static class can be used to generate randomised Boid position and velocity components.
*
*/
class RandomBoidPosVel
{
	static std::default_random_engine generator;
	static std::uniform_int_distribution<int> velDistribution;
	static std::uniform_int_distribution<int> posDistribution;

public:
	static void InitVel(int min, int max);
	static void InitPos(int min, int max);
	static int GetVelocityComp();
	static int GetPositionComp();
};

