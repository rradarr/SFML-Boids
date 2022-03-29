#include "SettingCardinality.h"

void SettingCardinality::Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<int*> _ints)
{
	ints = _ints;

	stringText = _text;
	//-----------------------------------------------
	slider.Initialize(origin);
	slider.SetValues(minVal, maxVal, _default);
	//-----------------------------------------------
	font.loadFromFile("Misc\\arial.ttf");
	sfText.setFont(font);
	sfText.setCharacterSize(25);
	sfText.setString(stringText);
	sfText.setPosition(origin.x - 11 - 70, origin.y - 25 - 15);
}

void SettingCardinality::Initialize()
{
}

void SettingCardinality::Initialize(BoidGroupSettings * _settingsPtr)
{
}

void SettingCardinality::Initialize(std::string _text, std::vector<bool*> _bools, std::vector<BoidGroup*> _boidGroupsAccess, int _function)
{
}

void SettingCardinality::Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<float*> _floats)
{
}

void SettingCardinality::CheckInputs(sf::Vector2f mousePosition, const int groupID)
{
	slider.SetCurrentValue(*ints[groupID]);
	slider.ProcessInput(mousePosition);
}

void SettingCardinality::Update(const int groupID)
{
	if (slider.IsPressed()) {
		sfText.setString(std::to_string(std::floor(slider.value)));
	}
	else {
		sfText.setString(stringText);
	}
	*ints[groupID] = std::floor(slider.value);
}

float SettingCardinality::GetValue()
{
	return std::floor(slider.value);
}

void SettingCardinality::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(slider);
	target.draw(sfText);
}
