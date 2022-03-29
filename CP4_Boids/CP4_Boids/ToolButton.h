#pragma once

#include <SFML/Graphics.hpp>

#include "Clickable.h"

/**
*This class represents a type of a button.
*
*This class implements virtual Clickable methods.
*/
class ToolButton : public Clickable, virtual public sf::Drawable
{
	sf::RectangleShape button;
	sf::Color uncheckedColor;

public:
	bool checked;
	bool justChecked;

	void Initialize(sf::Vector2f position);
	void ProcessInput(sf::Vector2f mousePosition);
	void Update();
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	void Check();
	void Uncheck();

};

