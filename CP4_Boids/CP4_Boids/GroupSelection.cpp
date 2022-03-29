#include "GroupSelection.h"

#include "InputReceiver.h"
#include "BoidGroupSettings.h"

void GroupSelection::Initialize(BoidGroupSettings* _settingsPtr)
{
	chosenID = 0;
	settingsPtr = _settingsPtr;
	
	//-----------------------------------------------
	IDbackground.setSize(sf::Vector2f(50, 50));
	IDbackground.setOrigin(IDbackground.getSize().x / 2, IDbackground.getSize().y / 2);
	IDbackground.setPosition(origin);
	IDbackground.setFillColor(settingsPtr->colours[chosenID]);
	//-----------------------------------------------
	font.loadFromFile("Misc\\arial.ttf");
	IDtext.setFont(font);
	IDtext.setCharacterSize(40);
	IDtext.setString(std::to_string(chosenID));
	IDtext.setPosition(origin.x - 11, origin.y - 25);
	//-----------------------------------------------
	arrowL.Initialize(sf::Vector2f(origin.x - 35, origin.y));
	arrowL.SetAngle(-90);
	arrowR.Initialize(sf::Vector2f(origin.x + 35, origin.y));
	arrowR.SetAngle(90);
}

void GroupSelection::Initialize()
{
}

void GroupSelection::Initialize(std::string _text, std::vector<bool*> _bools, std::vector<BoidGroup*> _boidGroupsAccess, int _function)
{
}

void GroupSelection::Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<float*> _floats)
{
}

void GroupSelection::Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<int*> _ints)
{
}

void GroupSelection::CheckInputs(sf::Vector2f mousePosition, const int groupID)
{
	arrowL.ProcessInput(mousePosition);
	arrowR.ProcessInput(mousePosition);
}

void GroupSelection::Update(const int groupID)
{
	if (arrowL.toggled)
		PrevGroup();
	else if (arrowR.toggled)
		NextGroup();

	IDbackground.setFillColor(settingsPtr->colours[chosenID]);
}

float GroupSelection::GetValue()
{
	return float(chosenID);
}

void GroupSelection::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(arrowL);
	target.draw(arrowR);
	target.draw(IDbackground);
	target.draw(IDtext);
}

void GroupSelection::NextGroup()
{
	chosenID = (chosenID + 1) % 6;
	IDtext.setString(std::to_string(chosenID));
}

void GroupSelection::PrevGroup()
{
	chosenID = chosenID - 1;
	if (chosenID < 0)
		chosenID = 5;
	IDtext.setString(std::to_string(chosenID));
}
