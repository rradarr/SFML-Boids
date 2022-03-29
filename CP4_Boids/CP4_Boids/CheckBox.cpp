#include "CheckBox.h"

#include "InputReceiver.h"

#include "BoidGroup.h"
#include "BoidGroupSettings.h"

void CheckBox::Initialize(std::string _text, std::vector<bool*> _bools, std::vector<BoidGroup*> _boidGroupsAccess, int _function)
{
	bools = _bools;
	function = _function;
	boidGroupsAccess = _boidGroupsAccess;

	box.Initialize(sf::Vector2f(origin.x - 75, origin.y));
	//-----------------------------------------------
	font.loadFromFile("Misc\\arial.ttf");
	text.setFont(font);
	text.setCharacterSize(25);
	text.setString(_text);
	text.setPosition(origin.x - 11 - 40, origin.y - 15);
}

void CheckBox::Initialize()
{
}

void CheckBox::Initialize(BoidGroupSettings * _settingsPtr)
{
}

void CheckBox::Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<float*> _floats)
{
}

void CheckBox::Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<int*> _ints)
{
}

void CheckBox::CheckInputs(sf::Vector2f mousePosition, const int groupID)
{
	box.SetValue(*bools[groupID]);
	box.ProcessInput(mousePosition);
}

void CheckBox::Update(const int groupID)
{
	if (*bools[groupID] != box.checked) {
		if (function == 0) {
			boidGroupsAccess[groupID]->togglePrey();
		}
		else {
			boidGroupsAccess[groupID]->togglePredator();
		}
	}
}

float CheckBox::GetValue()
{
	return float(box.checked);
}

void CheckBox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(box);
	target.draw(text);
}
