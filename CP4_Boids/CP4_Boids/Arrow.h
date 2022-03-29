#pragma once

#include <SFML/Graphics.hpp>

#include "Clickable.h"

/**
*This class represents an arrow button UI element.
*
*This class implements virtual Clickable methods.
*With this class a button in the shape of a triangle
*caan be created and used.
*/
class Arrow : public Clickable, public sf::Drawable
{
	sf::ConvexShape arrow;

public:
	bool toggled;
	
	void Initialize(sf::Vector2f position);
	void SetAngle(float angle);
	void ProcessInput(sf::Vector2f mousePosition);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

