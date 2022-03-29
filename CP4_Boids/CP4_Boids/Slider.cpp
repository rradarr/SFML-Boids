#include "Slider.h"

#include "InputReceiver.h"

bool Slider::IsPressed()
{
	return pressed;
}

void Slider::Initialize(sf::Vector2f position)
{
	guideColor = sf::Color(247, 247, 247);

	//--------------------------------------
	guide.setSize(sf::Vector2f(180, 5));
	guide.setOrigin(guide.getSize().x / 2, guide.getSize().y / 2);
	guide.setPosition(position);
	guide.setFillColor(guideColor);
	//--------------------------------------
	handle.setSize(sf::Vector2f(8, 20));
	handle.setOrigin(handle.getSize().x / 2, handle.getSize().y / 2);

	handle.setPosition(guide.getPosition());
	handle.setFillColor(Clickable::defaultColor);
}

void Slider::SetValues(float minVal, float maxVal, float _default)
{
	value = _default;
	xMin = guide.getPosition().x - guide.getSize().x / 2;
	xMax = guide.getPosition().x + guide.getSize().x / 2;
	maxValue = maxVal;
	minValue = minVal;
	slope = (maxValue - minValue) / (xMax - xMin);
	float defaultX = xMin + (value - minValue) / slope;

	handle.setPosition(defaultX, guide.getPosition().y);
}

void Slider::SetCurrentValue(float _value)
{
	value = _value;
	float positionX = xMin + (value - minValue) / slope;

	handle.setPosition(positionX, guide.getPosition().y);
}

void Slider::ProcessInput(sf::Vector2f mousePosition)
{
	if (InputReceiver::isPressed(InputReceiver::keyCodes::mouseL)) {
		if (handle.getGlobalBounds().contains(mousePosition) || guide.getGlobalBounds().contains(mousePosition)) {
			pressed = true;
			handle.setFillColor(Clickable::pressedColor);
		}
	}
	else if (InputReceiver::isReleased(InputReceiver::keyCodes::mouseL)) {
		if (pressed) {
			pressed = false;
			handle.setFillColor(Clickable::defaultColor);
		}
	}
	if (pressed)
		Update(mousePosition);
}

void Slider::Update(sf::Vector2f mousePosition)
{
	if (mousePosition.x < guide.getPosition().x - guide.getSize().x / 2) {
		handle.setPosition(guide.getPosition().x - guide.getSize().x / 2, handle.getPosition().y);
	}
	else if (mousePosition.x > guide.getPosition().x + guide.getSize().x / 2) {
		handle.setPosition(guide.getPosition().x + guide.getSize().x / 2, handle.getPosition().y);
	}
	else {
		handle.setPosition(mousePosition.x, handle.getPosition().y);
	}
	value = minValue + (slope * (handle.getPosition().x - xMin));
}

void Slider::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(guide);
	target.draw(handle);
}