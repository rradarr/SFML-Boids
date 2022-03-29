#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Simulation.h"
#include "Control.h"

class BoidGroup;

/**
*This class is the main interface of the whole application.
*
*This class stores and orchestrates all elements necessary for
*the application to work correctly.
*/
class Application
{
	Simulation simulation;
	Control control;
	std::vector<BoidGroup*> BoidGroupsAccess;

	sf::Clock clock;
	float deltaTime;
	sf::RenderWindow window;
	sf::Vector2i windowSize;
	int frameCount;

public:
	Application();
	~Application();

	void InitializeApplication(int population, int groups);

	/// Get keyboard inputs and process them.
	void ProcessInput();
	/// Update the simulation and UI.
	void Update();
	/// Perfom late update of the simulation.
	void LateUpdate();
	/// Draw the simulation to a window.
	void Draw();
	/// Check if the simulation is running.
	bool IsRunning() const;
	/// Get the time between frames.
	void GetDeltaTime();
};

