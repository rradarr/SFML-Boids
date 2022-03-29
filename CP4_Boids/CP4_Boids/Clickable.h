#pragma once

#include <SFML/Graphics.hpp>

/**
*This mostly virtual class is a generalization of all clickable elements.
*
*/
class Clickable
{
protected:
	bool pressed;

	sf::Color defaultColor = sf::Color(184, 184, 184);
	sf::Color pressedColor = sf::Color(94, 94, 94);

public:
	Clickable() = default;
	virtual ~Clickable() = default;
	virtual void Initialize(sf::Vector2f position) = 0;
	virtual void ProcessInput(sf::Vector2f mousePosition) = 0;
};

