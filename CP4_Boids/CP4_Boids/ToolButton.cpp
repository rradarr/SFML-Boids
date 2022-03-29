#include "ToolButton.h"

#include "InputReceiver.h"

void ToolButton::Initialize(sf::Vector2f position)
{
	pressed, checked, justChecked = false;
	uncheckedColor = sf::Color(204, 204, 204);

	button.setSize(sf::Vector2f(30, 30));
	button.setOrigin(button.getSize().x / 2, button.getSize().y / 2);
	button.setPosition(position);
	button.setFillColor(uncheckedColor);

	button.setOutlineThickness(3);
	button.setOutlineColor(defaultColor);
}

void ToolButton::ProcessInput(sf::Vector2f mousePosition)
{
	justChecked = false;
	if (InputReceiver::isPressed(InputReceiver::keyCodes::mouseL)) {
		if (button.getGlobalBounds().contains(mousePosition)) {
			pressed = true;
			button.setFillColor(defaultColor);
		}
	}
	else if (InputReceiver::isReleased(InputReceiver::keyCodes::mouseL)) {
		if (pressed) {
			pressed = false;
			justChecked = true;
			Check();
		}
	}
}

void ToolButton::Update()
{
}

void ToolButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(button);
}

void ToolButton::Check()
{
	checked = true;
	button.setFillColor(pressedColor);
}

void ToolButton::Uncheck()
{
	checked = false;
	button.setFillColor(uncheckedColor);
}
