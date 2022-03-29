#include "Simulation.h"

#include "RandomBoidPosVel.h"


void Simulation::InitializeSimulation(int population, int groups, sf::RenderWindow* _windowRef, std::vector<BoidGroup*>& accessPtr)
{
	lattice = BinLattice(60);
	windowRef = _windowRef;

	RandomBoidPosVel::InitVel(-10, 10);
	RandomBoidPosVel::InitPos(0, windowRef->getSize().x > windowRef->getSize().y ? windowRef->getSize().y - 1 : windowRef->getSize().x - 1);

	int i = 0;
	for (; i < groups && i < 6; i++) {
		boidGroups.emplace_front();
		boidGroups.begin()->InitBoidGroup(population, windowRef, &lattice, &simData);
		boidGroupsAccessPointers->push_back(&(*boidGroups.begin()));
	}
	for (; i < 6; i++) {
		boidGroups.emplace_front();
		boidGroups.begin()->InitBoidGroup(0, windowRef, &lattice, &simData);
		boidGroupsAccessPointers->push_back(&(*boidGroups.begin()));
	}
	accessPtr = *boidGroupsAccessPointers;
}

void Simulation::ProcessInput()
{
	
}

void Simulation::Update(float deltaTime)
{
	for (auto& group : boidGroups) {
		group.Update(deltaTime);
	}
}

void Simulation::LateUpdate()
{
	for (auto& group : boidGroups) {
		group.LateUpdate();
	}
}

void Simulation::Draw()
{
	for (auto& group : boidGroups) {
		group.Draw();
	}
}
