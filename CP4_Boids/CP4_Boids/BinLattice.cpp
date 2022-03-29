#include "BinLattice.h"

#include "Boid.h"
#include "BoidLatticeData.h"

BinLattice::BinLattice(int _binSize)
{
	//screen 1200 x 900
	binSize = _binSize;
	int xRes = 1200 / binSize;
	int yRes = 900 / binSize;

	for (int g = 0; g < 6; g++) {
		binLattice.push_back(std::vector<std::vector<std::list<Boid*>>>());
		for (int c = 0; c < xRes; c++) {
			binLattice[g].push_back(std::vector<std::list<Boid*>>());
			for (int r = 0; r < yRes; r++) {
				binLattice[g][c].push_back(std::list<Boid*>());
			}
		}
	}
}

void BinLattice::RegisterBoid(BoidLatticeData& data)
{
	int column = std::floor(data.boidOwner->GetPosition().x / binSize);
	int row = std::floor(data.boidOwner->GetPosition().y / binSize);

	if (data.column != -1) {
		if (column == data.column && row == data.row) {
			return;
		}
		binLattice[data.group][data.column][data.row].erase(data.listElement);
	}

	data.column = column;
	data.row = row;

	binLattice[data.group][data.column][data.row].push_front(data.boidOwner);
	data.listElement = binLattice[data.group][data.column][data.row].begin();
}

void BinLattice::DeleteBoid(BoidLatticeData & data)
{
	binLattice[data.group][data.column][data.row].erase(data.listElement);
	data.listElement = binLattice[data.group][data.column][data.row].end();
}
