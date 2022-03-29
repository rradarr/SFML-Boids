#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "PanelElement.h"
#include "Arrow.h"

class BoidGroupSettings;
class BoidGroup;

/**
*This class represents the Panel Element that allows for selecting a Boid Group.
*
*This class implements the virtual functions of Panel Element.
*Using this class a selection element can be added to the
*Panel with which the user can choose a boid group.
*It's chosenID value can be retrieved and is used
*by other elements to determine which group settings
*are being displayed and influenced.
*/
class GroupSelection : public PanelElement
{
	Arrow arrowL, arrowR;
	sf::RectangleShape IDbackground;
	sf::Text IDtext;
	sf::Font font;

	BoidGroupSettings* settingsPtr;
	int chosenID;

public:
	virtual void Initialize(BoidGroupSettings* _settingsPtr) override;
	void CheckInputs(sf::Vector2f mousePosition, const int groupID) override;
	void Update(const int groupID) override;
	float GetValue() override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;


	virtual void Initialize();
	virtual void Initialize(std::string _text, std::vector<bool*> _bools, std::vector<BoidGroup*> _boidGroupsAccess, int _function);
	virtual void Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<float*> _floats);
	virtual void Initialize(float minVal, float maxVal, float _default, std::string _text, std::vector<int*> _ints);

private:
	void NextGroup();
	void PrevGroup();
};

