#include "SettingTools.h"

#include "BoidGroupSettings.h"

void SettingTools::Initialize()
{
	ToolButton button;
	button.Initialize(sf::Vector2f(origin.x - 40, origin.y));
	buttons.push_back(button);

	ToolButton button2;
	button2.Initialize(sf::Vector2f(origin.x, origin.y));
	buttons.push_back(button2);
}

void SettingTools::Initialize(BoidGroupSettings* _settingsPtr)
{
}

void SettingTools::Initialize(std::string _text, std::vector<bool*> _bools, std::vector<BoidGroup*> _boidGroupsAccess, int _function)
{
}

void SettingTools::Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<float*> _floats)
{
}

void SettingTools::Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<int*> _ints)
{
}

void SettingTools::CheckInputs(sf::Vector2f mousePosition, const int groupID)
{
	for (auto& button : buttons) {
		button.ProcessInput(mousePosition);
	}
}

void SettingTools::Update(const int groupID)
{
	for (auto& button : buttons) {
		if (button.justChecked) {
			for (auto& button2 : buttons) {
				button2.Uncheck();
			}
			button.Check();
			break;
		}
	}

	if (buttons[0].checked) {
		BoidGroupSettings::SetTool(0);
	}
	else if (buttons[1].checked){
		BoidGroupSettings::SetTool(1);
	}
}

float SettingTools::GetValue()
{
	return float(chosenTool);
}

void SettingTools::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto& button : buttons) {
		target.draw(button);
	}
}
