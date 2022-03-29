#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "PanelElement.h"
#include "Slider.h"

class BoidGroupSettings;
class BoidGroup;

/**
*This class represents the Panel Element that is a slider.
*
*This class implements the virtual functions of Panel Element.
*Using this class a slider can be added to the Panel with which
*the user can set a float value.
*It modifies the values passed to it in Initialize as _floats.
*/
class SettingSlider : public PanelElement
{
	std::vector<float*> floats;

	Slider slider;
	sf::Text sfText;
	sf::Font font;

	std::string stringText;

public:
	virtual void Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<float*> _floats) override;
	void CheckInputs(sf::Vector2f mousePosition, const int groupID) override;
	void Update(const int groupID) override;
	float GetValue() override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;


	virtual void Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<int*> _ints);
	virtual void Initialize();
	virtual void Initialize(BoidGroupSettings* _settingsPtr);
	virtual void Initialize(std::string _text, std::vector<bool*> _bools, std::vector<BoidGroup*> _boidGroupsAccess, int _function);

};

