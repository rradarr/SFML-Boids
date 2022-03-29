#pragma once

#include <SFML/Graphics.hpp>

class BinLattice;
class SimulationData;

/**
*This class holds data describing a BoidGroup.
*
*This class serves as a container for all the data
*that a BoidGroup needs to function. It is also modified
*by the UI elements to control parameters of the simulation.
*/
class BoidGroupSettings
{
public:
	sf::RenderWindow* windowRef;
	SimulationData* simDataRef;

	int group;
	int cardinality;
	int desiredCardinality;

	bool isPrey;
	bool isPredator;
	BinLattice* lattice;

	static sf::Color colours[6];
	float constAcceleration;
	float maxVelocity;
	float maxForce;
	float sightDistance;

	float alignment, cohesion, separation;
	float preyForce, predatorForce;
	bool useTool;
	static int tool;
	
	BoidGroupSettings();
	static void SetTool(int _tool);
};