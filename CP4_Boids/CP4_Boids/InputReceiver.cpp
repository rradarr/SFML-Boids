#include "InputReceiver.h"

#include <SFML/Graphics.hpp>

int InputReceiver::keysThisFrame = 0;
int InputReceiver::keysLastFrame;
sf::Vector2f InputReceiver::mousePosition = sf::Vector2f(0, 0);

void InputReceiver::GetInputs(sf::RenderWindow* _windowRef)
{
	sf::Vector2i mouseScreen = sf::Mouse::getPosition(*_windowRef);
	mousePosition = _windowRef->mapPixelToCoords(mouseScreen);

	keysLastFrame = keysThisFrame;
	keysThisFrame = 0;


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		keysThisFrame = keysThisFrame | (1 << (int)keyCodes::mouseL);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		keysThisFrame = keysThisFrame | (1 << (int)keyCodes::mouseR);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		keysThisFrame = keysThisFrame | (1 << (int)keyCodes::spaceBar);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		keysThisFrame = keysThisFrame | (1 << (int)keyCodes::esc);
	}
}

bool InputReceiver::isPressed(keyCodes key)
{
	return (keysThisFrame & (1 << (int)key)) & ~(keysLastFrame & (1 << (int)key));
}

bool InputReceiver::isReleased(keyCodes key)
{
	return ~(keysThisFrame & (1 << (int)key)) & (keysLastFrame & (1 << (int)key));
}

bool InputReceiver::isHeld(keyCodes key)
{
	return keysThisFrame & (1 << (int)key);
}
