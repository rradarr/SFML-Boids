#pragma once

#include <memory>

#include "Boid.h"
#include "BoidGroupSettings.h"

class BinLattice;
class SimulationData;

/**
*This class represents a group of Boids.
*
*It holds a std::list of Boids as well as a unique pointer
*to BoidGroupSettings. It's responsible for separating boids from
*other groups, creation and coordinantion of Boid behaviour within a group.
*/
class BoidGroup
{
	static int id;
	std::list<Boid> boids;

public:
	std::unique_ptr<BoidGroupSettings> settings;
	BoidGroup() = default;

	BoidGroup& operator=(BoidGroup &&other)
	{
		if (&other == this)
			return *this;

		boids = std::move(other.boids);
		settings = std::move(other.settings);

		return *this;
	}

	~BoidGroup();

	void InitBoidGroup(int population, sf::RenderWindow* _windowRef, BinLattice* lattice, SimulationData* simData);
	void togglePrey();
	void togglePredator();
	void Update(float deltaTime);
	void LateUpdate();
	void Draw();

private:
	void MatchCardinality();
};

