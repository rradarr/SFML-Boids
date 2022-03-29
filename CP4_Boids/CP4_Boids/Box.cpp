#include "Box.h"

#include "InputReceiver.h"

void Box::Initialize(sf::Vector2f position)
{
	pressed, checked = false;
	uncheckedColor = sf::Color(204, 204, 204);

	box.setSize(sf::Vector2f(30, 30));
	box.setOrigin(box.getSize().x / 2, box.getSize().y / 2);
	box.setPosition(position);
	box.setFillColor(uncheckedColor);

	box.setOutlineThickness(3);
	box.setOutlineColor(defaultColor);
}

void Box::ProcessInput(sf::Vector2f mousePosition)
{
	if (InputReceiver::isPressed(InputReceiver::keyCodes::mouseL)) {
		if (box.getGlobalBounds().contains(mousePosition)) {
			pressed = true;
			box.setFillColor(defaultColor);
		}
	}
	else if (InputReceiver::isReleased(InputReceiver::keyCodes::mouseL)) {
		if (pressed) {
			pressed = false;
			if (!checked) {
				checked = true;
				box.setFillColor(pressedColor);
			}
			else {
				checked = false;
				box.setFillColor(uncheckedColor);
			}
		}
	}
}

void Box::SetValue(bool value)
{
	if (checked && !value) {
		checked = false;
		box.setFillColor(uncheckedColor);
	}
	else if (!checked && value) {
		checked = true;
		box.setFillColor(pressedColor);
	}
}

void Box::Update(sf::Vector2f mousePosition)
{
}

void Box::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(box);
}
