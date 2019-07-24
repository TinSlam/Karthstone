#pragma once

#include "Mewtle.h"

#include "Entities/Cards/BuildingCards/BuildingCard.h"

class BuildPhase{
	City* city;
	BuildingCard* card;
	Mewtle::Label* greyScreen;
	Mewtle::Entity* prototypeBuilding;
	City::ROTATION rotation = City::ROTATION::ZERO;

public:
	BuildPhase(BuildingCard* card, City* city);
	~BuildPhase();

	void start();
	void end();
	void tick();
	void render();

	bool mouseLeftReleased(double x, double y);
	bool mouseRightReleased(double x, double y);
	bool keyboardInput();
};
