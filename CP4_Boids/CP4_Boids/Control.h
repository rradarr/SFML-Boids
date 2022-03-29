#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "ControlPanel.h"

class BoidGroup;

/**
*This class provides a general interface for the user control and GUI panel.
*
*/
class Control
{
private:
	ControlPanel panel;

	sf::RenderWindow* windowRef;
	std::vector<BoidGroup*> boidGroupsAccess;

public:

	///Initializes the graphical control panel. Passes to it access to boid groups.
	void InitializeControl(sf::RenderWindow* _windowRef, std::vector<BoidGroup*> _boidGroupsAccess);
	///Handles all user inputs.
	void ProcessInputs();
	void Update();
	void Draw();
};

