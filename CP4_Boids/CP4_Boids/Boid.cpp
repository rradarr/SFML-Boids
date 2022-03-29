#include "Boid.h"

#include <cmath>

#include "BoidGroupSettings.h"
#include "BinLattice.h"
#include "SimulationData.h"

#define RADTODEG 57.295779578f

Boid::Boid(int randVelX, int randVelY, int randPosX, int randPosY, BoidGroupSettings * _settings)
{
	settings = _settings;

	latticeData.group = settings->group;

	boid.setPointCount(3);
	boid.setPoint(0, sf::Vector2f(0, 0));
	boid.setPoint(1, sf::Vector2f(12, 0));
	boid.setPoint(2, sf::Vector2f(6, -14));

	boid.setOrigin(6.f, -14.f / 3.f);

	boid.setPosition(randPosX, randPosY);
	boid.setFillColor(settings->colours[settings->group]);

	acceleration.x = float(randVelX);
	acceleration.y = float(randVelY);
	acceleration.Normalize();
	acceleration *= settings->maxForce;

	velocity += acceleration;
}

void Boid::FlockToMouse(sf::Vector2f worldMouseCoords, float multiplier)
{
	Vector<float> steerDirection;
	steerDirection = worldMouseCoords - boid.getPosition();
	steerDirection.Normalize();

	steerDirection *= settings->maxVelocity;
	steerDirection = steerDirection - this->velocity;
	steerDirection.Limit(settings->maxForce);
	
	acceleration += steerDirection * multiplier;
}

void Boid::FlockFromMouse(sf::Vector2f worldMouseCoords, float multiplier)
{
	Vector<float> steerDirection;
	steerDirection = boid.getPosition() - worldMouseCoords;
	steerDirection.Normalize();


	steerDirection *= settings->maxVelocity;
	steerDirection = steerDirection - this->velocity;
	steerDirection.Limit(settings->maxForce);

	acceleration += steerDirection * multiplier;
}

void Boid::Align(float multiplier)
{
	GetBins(localBinCols, localBinRows);
	
	Vector<float> directionAvg(0, 0);
	int counter = 0;

	for (int i = 0; i < 3; i++) {
		for (int l = 0; l < 3; l++) {
			for (auto& mate : settings->lattice->binLattice[settings->group][localBinCols[i]][localBinRows[l]]) {

				Vector<float> relative = this->boid.getPosition() - mate->boid.getPosition();
				if (this != mate && relative.GetMagnitude() < settings->sightDistance) {
					directionAvg += mate->velocity;
					counter++;
				}
			}
		}
	}

	if (counter > 0) {
		directionAvg /= float(counter);
		directionAvg.Normalize();
		directionAvg *= settings->maxVelocity;

		directionAvg = directionAvg - this->velocity;
		directionAvg.Limit(settings->maxForce);
	}
	this->acceleration += directionAvg * multiplier;
}

void Boid::Cohese(float multiplier)
{
	Vector<float> positionAvg(0, 0);
	int counter = 0;

	for (int i = 0; i < 3; i++) {
		for (int l = 0; l < 3; l++) {
			for (auto& mate : settings->lattice->binLattice[settings->group][localBinCols[i]][localBinRows[l]]) {

				Vector<float> relative = this->boid.getPosition() - mate->boid.getPosition();
				if (this != mate && relative.GetMagnitude() < settings->sightDistance && relative.GetMagnitude() > 0.f) {
					positionAvg += mate->boid.getPosition();
					counter++;
				}
			}
		}
	}

	if (counter > 0) {
		positionAvg /= float(counter);
		positionAvg = positionAvg - this->boid.getPosition();
		positionAvg.Normalize();
		positionAvg *= settings->maxVelocity;

		positionAvg = positionAvg - this->velocity;
		positionAvg.Limit(settings->maxForce);
	}
	acceleration += positionAvg * multiplier;
}

void Boid::Separate(float multiplier)
{
	Vector<float> repulsionAvg(0, 0);
	int counter = 0;

	for (int i = 0; i < 3; i++) {
		for (int l = 0; l < 3; l++) {
			for (auto& mate : settings->lattice->binLattice[settings->group][localBinCols[i]][localBinRows[l]]) {

				Vector<float> relative = this->boid.getPosition() - mate->boid.getPosition();
				if (relative.GetMagnitude() < settings->sightDistance * 0.5f && this != mate && relative.GetMagnitude() > 0.f) {
					repulsionAvg += relative / std::powf(relative.GetMagnitude(), 2);
					counter++;
				}
			}
		}
	}

	if (counter > 0) {
		repulsionAvg /= float(counter);
		repulsionAvg.Normalize();
		repulsionAvg *= settings->maxVelocity;

		repulsionAvg = repulsionAvg - this->velocity;
		repulsionAvg.Limit(settings->maxForce);
	}
	acceleration += repulsionAvg * multiplier;
}

void Boid::Flee(float multiplier)
{
	Vector<float> fleeAvg(0, 0);
	int counter = 0;

	for (int group : settings->simDataRef->predatorGroups) {
		for (int i = 0; i < 3; i++) {
			for (int l = 0; l < 3; l++) {
				for (auto& mate : settings->lattice->binLattice[group][localBinCols[i]][localBinRows[l]]) {

					Vector<float> relative = this->boid.getPosition() - mate->boid.getPosition();
					float magnitude = relative.GetMagnitude();

					if (magnitude < settings->sightDistance && magnitude > 0.f) {
						fleeAvg += relative / std::powf(magnitude, 2);
						counter++;
					}

				}
			}
		}
	}

	if (counter > 0) {
		fleeAvg /= float(counter);
		fleeAvg.Normalize();
		fleeAvg *= settings->maxVelocity;

		fleeAvg = fleeAvg - this->velocity;
		fleeAvg.Limit(settings->maxForce);
	}
	acceleration += fleeAvg * multiplier;

}

void Boid::Hunt(float multiplier)
{
	Vector<float> huntAvg(0, 0);
	int counter = 0;

	for (int group : settings->simDataRef->preyGroups) {
		for (int i = 0; i < 3; i++) {
			for (int l = 0; l < 3; l++) {
				for (auto& mate : settings->lattice->binLattice[group][localBinCols[i]][localBinRows[l]]) {

					Vector<float> relative = mate->boid.getPosition() - this->boid.getPosition();
					float magnitude = relative.GetMagnitude();

					if (magnitude < settings->sightDistance && magnitude > 0.f) {
						huntAvg += relative / std::powf(magnitude, 2);
						counter++;
					}

				}
			}
		}
	}

	if (counter > 0) {
		huntAvg /= float(counter);
		huntAvg.Normalize();
		huntAvg *= settings->maxVelocity;

		huntAvg = huntAvg - this->velocity;
		huntAvg.Limit(settings->maxForce);

	}
	acceleration += huntAvg * multiplier;
}

void Boid::Update(float deltaTime)
{
	acceleration.Limit(settings->maxForce);
	velocity += acceleration;
	velocity.Limit(settings->maxVelocity);

	boid.setPosition(boid.getPosition() + velocity * deltaTime);
	boid.setRotation(180 - atan2f(velocity.x, velocity.y) * RADTODEG);
	this->UpdateColour();

	acceleration *= 0.f;
}

void Boid::LateUpdate()
{
	Vector<float> newLocation = boid.getPosition();

	if (newLocation.x < 0) {
		newLocation.x = settings->windowRef->getSize().x - 0.01f;
	}
	else if (newLocation.x >= settings->windowRef->getSize().x) {
		newLocation.x = 0;
	}

	if (newLocation.y < 0) {
		newLocation.y = settings->windowRef->getSize().y - 0.01f;
	}
	else if (newLocation.y >= settings->windowRef->getSize().y) {
		newLocation.y = 0;
	}

	boid.setPosition(newLocation);

	settings->lattice->RegisterBoid(latticeData);
}

void Boid::setLatticeDataBoidPointer(Boid* boidPointer)
{
	latticeData.boidOwner = boidPointer;
	settings->lattice->RegisterBoid(latticeData);
}

void Boid::DeleteFromLattice()
{
	settings->lattice->DeleteBoid(latticeData);
	latticeData.boidOwner = nullptr;
}

sf::Vector2f Boid::GetPosition()
{
	return boid.getPosition();
}

void Boid::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(boid);
}

void Boid::UpdateColour()
{
	float rot = boid.getRotation();
	sf::Color col = settings->colours[settings->group];
	float valueModifier = std::abs(std::cosf(rot * 2 / RADTODEG)) * 0.75f + 0.25f;
	col.r = valueModifier * col.r;
	col.g = valueModifier * col.g;
	col.b = valueModifier * col.b;
	boid.setFillColor(col);
}

void Boid::GetBins(int col[3], int row[3])
{
	col[0] = latticeData.column - 1 < 0 ? settings->lattice->binLattice[0].size() - 1 : latticeData.column - 1;
	col[1] = latticeData.column;
	col[2] = latticeData.column + 1 >= settings->lattice->binLattice[0].size() ? 0 : latticeData.column + 1;

	row[0] = latticeData.row - 1 < 0 ? settings->lattice->binLattice[0][0].size() - 1 : latticeData.row - 1;
	row[1] = latticeData.row;
	row[2] = latticeData.row + 1 >= settings->lattice->binLattice[0][0].size() ? 0 : latticeData.row + 1;
}
