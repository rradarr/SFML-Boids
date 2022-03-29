#pragma once

#include <vector>

/**
*This class holds predator and prey group IDs of the simulation.
*
*/
class SimulationData
{
public:
	std::vector<int> preyGroups;
	std::vector<int> predatorGroups;
};

