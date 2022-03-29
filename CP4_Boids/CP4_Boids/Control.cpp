#include "Control.h"

#include <SFML/Graphics.hpp>

#include "InputReceiver.h"
#include "BoidGroup.h"
#include "BoidGroupSettings.h"

void Control::InitializeControl(sf::RenderWindow * _windowRef, std::vector<BoidGroup*> _boidGroupsAccess)
{
	windowRef = _windowRef;
	boidGroupsAccess = _boidGroupsAccess;
	panel.InitializeControlPanel(_windowRef, _boidGroupsAccess);
}

void Control::ProcessInputs()
{
	InputReceiver::GetInputs(windowRef);
	
	if (!panel.GetActive() || InputReceiver::mousePosition.x > panel.GetWidth()) {
		if (InputReceiver::isHeld(InputReceiver::keyCodes::mouseR)) {
			for (auto group : boidGroupsAccess) {
				group->settings->useTool = true;
			}
		}
		else if (InputReceiver::isHeld(InputReceiver::keyCodes::mouseL)) {
			boidGroupsAccess[panel.GetChosenID()]->settings->useTool = true;
		}
	}
	
	panel.ProcessInputs();
}

void Control::Update()
{
	panel.Update();
}

void Control::Draw()
{
	windowRef->draw(panel);
}
