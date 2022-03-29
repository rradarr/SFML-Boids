#include "ControlPanel.h"

#include <iterator>

#include "InputReceiver.h"
#include "GroupSelection.h"
#include "SettingCardinality.h"
#include "CheckBox.h"
#include "SettingSlider.h"
#include "SettingTools.h"

#include "BoidGroup.h"
#include "BoidGroupSettings.h"


void ControlPanel::InitializeControlPanel(sf::RenderWindow * _windowRef, std::vector<BoidGroup*> _boidGroupsAccess)
{
	windowRef = _windowRef;
	boidGroupsAccess = _boidGroupsAccess;
	isActive = true;

	panelBackground.setPosition(0, 0);
	panelBackground.setSize(sf::Vector2f(200, 900));
	panelBackground.setFillColor(sf::Color(194, 174, 118, 105));
	//---------------------------------------
	elements.emplace_back(new GroupSelection());
	elements.back()->SetOriginPosition(panelBackground.getSize().x / 2, 40);
	elements.back()->Initialize(boidGroupsAccess[0]->settings.get());
	//---------------------------------------
	std::vector<int*> ints;
	elements.emplace_back(new SettingCardinality());
	elements.back()->SetOriginPosition(panelBackground.getSize().x / 2, 150);

	for (int i = 0; i < 6; i++) {
		ints.push_back(&((boidGroupsAccess[i])->settings->desiredCardinality));
	}
	elements.back()->Initialize(0, 1000, 100, "Cardinality", ints);
	//---------------------------------------
	std::vector<float*> floats;

	elements.emplace_back(new SettingSlider());
	elements.back()->SetOriginPosition(panelBackground.getSize().x / 2, 220);
	floats.clear();
	for (int i = 0; i < 6; i++) {
		floats.push_back(&((boidGroupsAccess[i])->settings->alignment));
	}
	elements.back()->Initialize(0, 4, 1, "Alignment", floats);
	//-----------------
	elements.emplace_back(new SettingSlider());
	elements.back()->SetOriginPosition(panelBackground.getSize().x / 2, 290);
	floats.clear();
	for (int i = 0; i < 6; i++) {
		floats.push_back(&((boidGroupsAccess[i])->settings->cohesion));
	}
	elements.back()->Initialize(0, 4, 1, "Cohesion", floats);
	//-----------------
	elements.emplace_back(new SettingSlider());
	elements.back()->SetOriginPosition(panelBackground.getSize().x / 2, 360);
	floats.clear();
	for (int i = 0; i < 6; i++) {
		floats.push_back(&((boidGroupsAccess[i])->settings->separation));
	}
	elements.back()->Initialize(0, 4, 1.2f, "Separation", floats);
	//---------------------------------------
	std::vector<bool*> bools;

	elements.emplace_back(new CheckBox());
	elements.back()->SetOriginPosition(panelBackground.getSize().x / 2, 430);
	bools.clear();
	for (int i = 0; i < 6; i++) {
		bools.push_back(&((boidGroupsAccess[i])->settings->isPrey));
	}
	elements.back()->Initialize("Prey", bools, boidGroupsAccess, 0);
	//-----------------
	elements.emplace_back(new SettingSlider());
	elements.back()->SetOriginPosition(panelBackground.getSize().x / 2, 500);
	floats.clear();
	for (int i = 0; i < 6; i++) {
		floats.push_back(&((boidGroupsAccess[i])->settings->preyForce));
	}
	elements.back()->Initialize(0, 20, 10, "Prey force", floats);
	//-----------------
	elements.emplace_back(new CheckBox());
	elements.back()->SetOriginPosition(panelBackground.getSize().x / 2, 570);
	bools.clear();
	for (int i = 0; i < 6; i++) {
		bools.push_back(&((boidGroupsAccess[i])->settings->isPredator));
	}
	elements.back()->Initialize("Predator", bools, boidGroupsAccess, 1);
	//-----------------
	elements.emplace_back(new SettingSlider());
	elements.back()->SetOriginPosition(panelBackground.getSize().x / 2, 640);
	floats.clear();
	for (int i = 0; i < 6; i++) {
		floats.push_back(&((boidGroupsAccess[i])->settings->predatorForce));
	}
	elements.back()->Initialize(0, 20, 10, "Predator force", floats);
	//---------------------------------------
	elements.emplace_back(new SettingSlider());
	elements.back()->SetOriginPosition(panelBackground.getSize().x / 2, 740);
	floats.clear();
	for (int i = 0; i < 6; i++) {
		floats.push_back(&((boidGroupsAccess[i])->settings->maxForce));
	}
	elements.back()->Initialize(0, 15, 8, "Agility", floats);
	//---------------------------------------
	elements.emplace_back(new SettingTools());
	elements.back()->SetOriginPosition(panelBackground.getSize().x / 2, 850);
	elements.back()->Initialize();
}

void ControlPanel::ProcessInputs()
{
	if (isActive) {
		int groupID = elements[0]->GetValue();

		if (InputReceiver::mousePosition.x < panelBackground.getSize().x) {
			for (auto& element : elements) {
				element->CheckInputs(InputReceiver::mousePosition, groupID);
			}
		}
	}
	if (InputReceiver::isReleased(InputReceiver::keyCodes::spaceBar)) {
		this->Toggle();
	}
}

void ControlPanel::Update()
{
	int groupID = elements[0]->GetValue();
	for (auto& element : elements) {
		element->Update(groupID);
	}
}

void ControlPanel::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (isActive) {
		target.draw(panelBackground);
		for (auto& element : elements) {
			target.draw(*element);
		}
	}
}

bool ControlPanel::GetActive()
{
	return isActive;
}

float ControlPanel::GetWidth()
{
	return panelBackground.getSize().x;
}

int ControlPanel::GetChosenID()
{
	return elements[0]->GetValue();
}

void ControlPanel::Toggle()
{
	isActive = !isActive;
}
