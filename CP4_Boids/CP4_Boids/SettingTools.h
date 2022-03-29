#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "PanelElement.h"
#include "ToolButton.h"

class BoidGroupSettings;
class BoidGroup;

/**
*This class represents the Panel Element that is a group of tool buttons.
*
*This class implements the virtual functions of Panel Element.
*Using this class tool buttons can be added to the Panel with which
*the user can choose one tool they will use with mouse clicks.
*/
class SettingTools : public PanelElement
{
	std::vector<ToolButton> buttons;

	int chosenTool;

public:
	virtual void Initialize() override;
	void CheckInputs(sf::Vector2f mousePosition, const int groupID) override;
	void Update(const int groupID) override;
	float GetValue() override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;


	virtual void Initialize(BoidGroupSettings* _settingsPtr);
	virtual void Initialize(std::string _text, std::vector<bool*> _bools, std::vector<BoidGroup*> _boidGroupsAccess, int _function);
	virtual void Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<float*> _floats);
	virtual void Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<int*> _ints);
};

