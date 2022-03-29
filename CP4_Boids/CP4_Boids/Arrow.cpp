#include "Arrow.h"

#include "InputReceiver.h"

void Arrow::Initialize(sf::Vector2f position)
{
	pressed, toggled = false;

	arrow.setPointCount(3);
	arrow.setPoint(0, sf::Vector2f(0, 0));
	arrow.setPoint(1, sf::Vector2f(12, 0));
	arrow.setPoint(2, sf::Vector2f(6, -5));

	arrow.setOrigin(6.f, -5.f / 3.f);

	arrow.setScale(2, 2);

	arrow.setPosition(position);
	arrow.setFillColor(defaultColor);
}

void Arrow::SetAngle(float angle)
{
	arrow.setRotation(angle);
}

void Arrow::ProcessInput(sf::Vector2f mousePosition)
{
	toggled = false;
	if (InputReceiver::isPressed(InputReceiver::keyCodes::mouseL)) {
		if (arrow.getGlobalBounds().contains(mousePosition)) {
			pressed = true;
			arrow.setFillColor(pressedColor);
		}
	}
	else if (InputReceiver::isReleased(InputReceiver::keyCodes::mouseL)) {
		if (pressed) {
			pressed = false;
			toggled = true;
			arrow.setFillColor(defaultColor);
		}
	}
}

void Arrow::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(arrow);
}
