#pragma once

#include <vector>
#include <list>

#include <SFML/Graphics.hpp>

#include "BoidGroup.h"
#include "BinLattice.h"
#include "SimulationData.h"

/**
*This class represents the simulation part of the application.
*
*This class holds, initializes and coordinates the BinLattice and
*BoidGroups. It also holds SimulationData and pointers to boid groups
*that are pased over to the Control part so the UI can alter parameters of
*BoidGroups.
*/
class Simulation
{
	sf::RenderWindow* windowRef;

	BinLattice lattice;
	std::list<BoidGroup> boidGroups;
	std::vector<BoidGroup*> boidGroupsAccessPointers[6];
	SimulationData simData;

public:

	void InitializeSimulation(int population, int groups, sf::RenderWindow* _windowRef, std::vector<BoidGroup*>& accessPtr);
	void ProcessInput();
	void Update(float deltaTime);
	void LateUpdate();
	void Draw();
};

