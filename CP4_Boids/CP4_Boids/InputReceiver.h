#pragma once

#include <SFML/Graphics.hpp>

/**
*This static class recieves and interpretes keyboard and mouse input.
*
*This class holds two ints which  are used to store information about pressed keys.
*A bit with left shift equivalent to the code of a key tells us wheter the key is down or not.
*Storing keys that were down last frame and those that are down this frame allows for
*more control by recognizing if a key was just pressed, just released or is being held down.
*The class also stores the position of the mouse in the program window.
*The method GetInputs Needs to be run every frame before accessing any infromation
*from this class.
*/
class InputReceiver
{
	static int keysThisFrame;
	static int keysLastFrame;

public:
	static sf::Vector2f mousePosition;
	
	enum class keyCodes
	{
		mouseL = 0,
		mouseR = 1,
		spaceBar = 2,
		esc = 3
	};

	static void GetInputs(sf::RenderWindow * _windowRef);

	static bool isPressed(keyCodes key);

	static bool isReleased(keyCodes key);

	static bool isHeld(keyCodes key);

};

