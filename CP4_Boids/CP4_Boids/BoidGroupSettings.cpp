#include "BoidGroupSettings.h"

sf::Color BoidGroupSettings::colours[6] = { sf::Color(112, 166, 255) , sf::Color(157, 68, 199) , sf::Color(82, 171, 79) , sf::Color(199, 129, 68), sf::Color(189, 26, 26), sf::Color(214, 211, 41) };
int BoidGroupSettings::tool = 0;

BoidGroupSettings::BoidGroupSettings()
{
	windowRef = nullptr;
	simDataRef = nullptr;
	lattice = nullptr;

	group = 0;
	cardinality = 0;
	desiredCardinality = 0;

	isPrey = false;
	isPredator = false;

	constAcceleration = 3.f;
	maxVelocity = 250;
	maxForce = 8;
	sightDistance = 60;
	alignment = 1;
	cohesion = 1;
	separation = 1.2f;

	preyForce = 10;
	predatorForce = 10;

	useTool = false;
}

void BoidGroupSettings::SetTool(int _tool)
{
	tool = _tool;
}
