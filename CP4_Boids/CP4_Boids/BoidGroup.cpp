#include <iostream>
#include <random>
#include <algorithm>

#include "BoidGroup.h"
#include "BinLattice.h"
#include "SimulationData.h"
#include "InputReceiver.h"
#include "RandomBoidPosVel.h"

int BoidGroup::id = -1;

BoidGroup::~BoidGroup()
{
	std::cout << "Destructor called\n";
}

void BoidGroup::InitBoidGroup(int population, sf::RenderWindow* _windowRef, BinLattice * lattice, SimulationData* simData)
{
	std::cout << "Constructor called\n";
	id++;

	settings = std::make_unique<BoidGroupSettings>();
	settings->windowRef = _windowRef;
	settings->simDataRef = simData;
	settings->lattice = lattice;
	settings->group = id;
	settings->desiredCardinality = population;

	MatchCardinality();
}

void BoidGroup::togglePrey()
{
	if (settings->isPrey) {
		settings->isPrey = false;

		auto& preyGroups = settings->simDataRef->preyGroups;
		preyGroups.erase(std::remove(preyGroups.begin(), preyGroups.end(), settings->group), preyGroups.end());
	}
	else {
		settings->isPredator = false;
		settings->isPrey = true;

		auto& predatorGroups = settings->simDataRef->predatorGroups;
		predatorGroups.erase(std::remove(predatorGroups.begin(), predatorGroups.end(), settings->group), predatorGroups.end());

		settings->simDataRef->preyGroups.push_back(settings->group);
	}
}

void BoidGroup::togglePredator()
{
	if (settings->isPredator) {
		settings->isPredator = false;

		auto& predatorGroups = settings->simDataRef->predatorGroups;
		predatorGroups.erase(std::remove(predatorGroups.begin(), predatorGroups.end(), settings->group), predatorGroups.end());
	}
	else {
		settings->isPrey = false;
		settings->isPredator = true;

		auto& preyGroups = settings->simDataRef->preyGroups;
		preyGroups.erase(std::remove(preyGroups.begin(), preyGroups.end(), settings->group), preyGroups.end());

		settings->simDataRef->predatorGroups.push_back(settings->group);
	}
}

void BoidGroup::Update(float deltaTime)
{
	if (settings->useTool) {
		if (settings->tool == 0) {
			for (auto& boid : boids) {
				boid.FlockToMouse(InputReceiver::mousePosition, 8.f);
			}
		}
		else {
			for (auto& boid : boids) {
				boid.FlockFromMouse(InputReceiver::mousePosition, 8.f);
			}
		}		
	}
	else {
		for (auto& boid : boids) {
			boid.Align(settings->alignment);
			boid.Cohese(settings->cohesion);
			boid.Separate(settings->separation);
		}
		if (settings->simDataRef->preyGroups.size() > 0 && settings->simDataRef->predatorGroups.size() > 0) {
			for (auto& boid : boids) {
				if (settings->isPrey) {
					boid.Flee(settings->preyForce);
				}
				else if (settings->isPredator) {
					boid.Hunt(settings->predatorForce);
				}
			}
		}
	}
	for (auto& boid : boids) {
		boid.Update(deltaTime);
	}
}

void BoidGroup::LateUpdate()
{
	int i = 0;
	for (auto& boid : boids) {
		boid.LateUpdate();
		i++;
	}
	settings->useTool = false;

	MatchCardinality();
}

void BoidGroup::Draw()
{
	for (auto& boid : boids) {
		settings->windowRef->draw(boid);
	}
}

void BoidGroup::MatchCardinality()
{
	if (settings->cardinality == settings->desiredCardinality) {
		return;
	}
	else if (settings->cardinality < settings->desiredCardinality) {
		for (int i = 0; i < settings->desiredCardinality - settings->cardinality; i++) {
			boids.emplace_front(RandomBoidPosVel::GetVelocityComp(), RandomBoidPosVel::GetVelocityComp(), RandomBoidPosVel::GetPositionComp(), RandomBoidPosVel::GetPositionComp(), settings.get());
			boids.front().setLatticeDataBoidPointer(&boids.front());
		}
		settings->cardinality = settings->desiredCardinality;
	}
	else {
		for (int i = 0; i < settings->cardinality - settings->desiredCardinality; i++) {
			boids.back().DeleteFromLattice();
			boids.pop_back();
		}
		settings->cardinality = settings->desiredCardinality;
	}
}
