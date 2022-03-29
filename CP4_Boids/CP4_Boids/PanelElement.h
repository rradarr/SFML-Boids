#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class BoidGroupSettings;
class BoidGroup;


/**
*This class is mostly virtual and represents an element of the control panel.
*
*This class provides a unified interface for all Control Panel Elements. It also makes
*it possible to store the elements in a single container. It stores the origin position
*of a Panel Element and inherits from sf::Drawable since all panel elements are Drawable.
*/
class PanelElement : public sf::Drawable
{
protected:
	sf::Vector2f origin;

public:
	void SetOriginPosition(float x, float y);
	virtual void Initialize(BoidGroupSettings* _settingsPtr) = 0;
	virtual void Initialize() = 0;
	virtual void Initialize(std::string _text, std::vector<bool*> _bools, std::vector<BoidGroup*> _boidGroupsAccess, int _function) = 0;
	virtual void Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<float*> _floats) = 0;
	virtual void Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<int*> _ints) = 0;
	virtual void CheckInputs(sf::Vector2f mousePosition, const int groupID) = 0;
	virtual void Update(const int groupID) = 0;
	virtual float GetValue() = 0;
};

