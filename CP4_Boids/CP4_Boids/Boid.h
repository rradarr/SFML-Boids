#pragma once

#include <vector>

#include "Vector.h"
#include "BoidLatticeData.h"

class BoidGroupSettings;

/**
*This class represents a Boid.
*
*A Boid is an element of the complex system. It has rules
*that dictate it's movement. It uses the BinLattice data structure
*to perform queries for nereby Boids. At every frame an Acceleration vector
*is calculated based on the movement rules. Then that acceleration is added to
*the velocity of the Boid.
*/
class Boid : virtual public sf::Drawable
{
	sf::ConvexShape boid;
	BoidGroupSettings* settings;
	Vector<float> velocity;
	Vector<float> acceleration;
	int localBinCols[3], localBinRows[3];

	BoidLatticeData latticeData;

public:

	Boid(int randVelX, int randVelY, int randPosX, int randPosY, BoidGroupSettings* _settings);

	bool operator != (const Boid& right) {
		return this->acceleration != right.acceleration || this->velocity != right.velocity || this->boid.getPosition() != right.boid.getPosition();
	}

	void FlockToMouse(sf::Vector2f worldMouseCoords, float multiplier);
	void FlockFromMouse(sf::Vector2f worldMouseCoords, float multiplier);

	void Align(float multiplier);
	void Cohese(float multiplier);
	void Separate(float multiplier);

	void Flee(float multiplier);
	void Hunt(float multiplier);
	
	void Update(float deltaTime);
	void LateUpdate();

	void setLatticeDataBoidPointer(Boid* boidPointer);
	void DeleteFromLattice();

	sf::Vector2f GetPosition();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	void UpdateColour();
	void GetBins(int col[3], int row[3]);
};
