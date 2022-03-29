#pragma once

#include <list>

class Boid;
/**
*This class stores Boid specific data needed for BinLattice operations.
*
*This class stres data that is used when a boid is registered or deleted
*from a BinLattice. This approach prioritizes speed effeciency over space
*effeciency.
*/

class BoidLatticeData
{
public:
	int column;
	int row;
	int group;

	Boid* boidOwner;
	std::list<Boid*>::iterator listElement;

	BoidLatticeData();
};