#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "PanelElement.h"

class BoidGroup;

/**
*This class represents the graphical control panel.
*
*This class handles inputs of the control panel and stores
*elements that make up the panel. Using the control panel
*the user can manipulate parameters of the simulation.
*/
class ControlPanel : virtual public sf::Drawable
{
	sf::RenderWindow* windowRef;
	std::vector<BoidGroup*> boidGroupsAccess;

	sf::RectangleShape panelBackground;
	std::vector<std::unique_ptr<PanelElement>> elements;

	bool isActive;

public:
	///Initializes the panel by setting up the panel elements and stores pointers to them in the elements vector.
	void InitializeControlPanel(sf::RenderWindow* _windowRef, std::vector<BoidGroup*> _boidGroupsAccess);
	///Processes inputs to the elements and toggle the panel on and off.
	void ProcessInputs();
	///Updates all elements for the chosen Boid Group.
	void Update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool GetActive();
	float GetWidth();
	int GetChosenID();

private:
	///Toggles the panel on and off.
	void Toggle();
};