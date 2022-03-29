#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "Clickable.h"

/**
*This class represents a slider UI element.
*
*This class implements virtual Clickable methods.
*With this class the x position coordinate of the slider
*handle can be mapped to a range of float values.
*/
class Slider : public Clickable, public sf::Drawable
{
	sf::RectangleShape guide;
	sf::RectangleShape handle;

	sf::Color guideColor;

	float minValue, maxValue;
	float xMin, xMax;
	float slope;

public:
	float value;
	
	bool IsPressed();

	void Initialize(sf::Vector2f position);
	void SetValues(float minVal, float maxVal, float _default);
	void SetCurrentValue(float _value);
	void ProcessInput(sf::Vector2f mousePosition);
	void Update(sf::Vector2f mousePosition);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

