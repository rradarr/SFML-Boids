#pragma once

#include <vector>
#include <list>

class Boid;
class BoidLatticeData;

/**
*This class represents a dynamic data structure holding pointers to boids based on their location.
*
*This is an implementation of a Bin-lattice spatial subdivision dynamic data structure.
*It stores pointers to boids in Bins based on their location in the Simulation.
*It stores boids from all groups. The pointers are stored in lists to achive fast
*adding and removing of elements.
*/
class BinLattice
{
	int binSize;
public:
	std::vector<std::vector<std::vector<std::list<Boid*>>>> binLattice;

	BinLattice() = default;
	BinLattice(int binSize);

	void RegisterBoid(BoidLatticeData& data);
	void DeleteBoid(BoidLatticeData& data);
};

