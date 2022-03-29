#include "SettingSlider.h"

#include "InputReceiver.h"

#include "BoidGroupSettings.h"

void SettingSlider::Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<float*> _floats)
{
	floats = _floats;

	stringText = _text;
	//-----------------------------------------------
	slider.Initialize(origin);
	slider.SetValues(minVal, maxVal, _default);
	//-----------------------------------------------
	if (font.loadFromFile("Misc\\arial.ttf")) {
		//an exception maybe??
	}
	sfText.setFont(font);
	sfText.setCharacterSize(25);
	sfText.setString(stringText);
	sfText.setPosition(origin.x - 11 - 70, origin.y - 25 - 15);
}

void SettingSlider::Initialize()
{
}

void SettingSlider::Initialize(BoidGroupSettings * _settingsPtr)
{
}

void SettingSlider::Initialize(std::string _text, std::vector<bool*> _bools, std::vector<BoidGroup*> _boidGroupsAccess, int _function)
{
}

void SettingSlider::Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<int*> _ints)
{
}

void SettingSlider::CheckInputs(sf::Vector2f mousePosition, const int groupID)
{
	slider.SetCurrentValue(*floats[groupID]);
	slider.ProcessInput(mousePosition);
}

void SettingSlider::Update(const int groupID)
{
	if (slider.IsPressed()) {
		sfText.setString(std::to_string(slider.value));
	}
	else {
		sfText.setString(stringText);
	}
	*floats[groupID] = slider.value;
}

float SettingSlider::GetValue()
{
	return slider.value;
}

void SettingSlider::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(slider);
	target.draw(sfText);
}
