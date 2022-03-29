#pragma once

#include <SFML/Graphics.hpp>

#include "Clickable.h"

/**
*This class represents a box UI element.
*
*This class implements virtual Clickable methods.
*With this class a box UI element can be created.
*It caan be checked anad unchecked by the user using mouse.
*/
class Box : public Clickable, public sf::Drawable
{
	sf::RectangleShape box;
	sf::Color uncheckedColor;
public:
	bool checked;

	void Initialize(sf::Vector2f position);
	void ProcessInput(sf::Vector2f mousePosition);
	void SetValue(bool value);
	void Update(sf::Vector2f mousePosition);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	~Box() = default;
};

