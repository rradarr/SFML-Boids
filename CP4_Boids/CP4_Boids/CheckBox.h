#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "PanelElement.h"
#include "Box.h"

class BoidGroupSettings;
class BoidGroup;

/**
*This class represents a check box Panel Element with a label.
*
*This class implements the virtual functions of Panel Element.
*Using this class a check box can be added to the Panel which the user
*can toggle using the mouse. It uses methods of BoidGroup to directly
*influence it. I alters the values passed in Initialize as _bools.
*/
class CheckBox : public PanelElement
{
	std::vector<bool*> bools;
	std::vector<BoidGroup*> boidGroupsAccess;

	Box box;
	sf::Text text;
	sf::Font font;

	int function;

public:
	virtual void Initialize(std::string _text, std::vector<bool*> _bools, std::vector<BoidGroup*> _boidGroupsAccess, int _function) override;
	void CheckInputs(sf::Vector2f mousePosition, const int groupID) override;
	void Update(const int groupID) override;
	float GetValue() override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	
	
	virtual void Initialize();
	virtual void Initialize(BoidGroupSettings* _settingsPtr);
	virtual void Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<float*> _floats);
	virtual void Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<int*> _ints);
};

