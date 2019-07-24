#pragma once

#include "Entities/Cards/Card.h"
#include "Entities/Buildings/Building.h"

class BuildingCard : public Card{
	Building* building;

public:
	BuildingCard(int id, std::string name, int textureId, Building* building);
	~BuildingCard();

	void onPlay();
	virtual void onPlayBuildingCard() = 0;
	virtual void onDraw() = 0;
	virtual void onDiscard() = 0;
	virtual void endTurnAction() = 0;
	virtual void startTurnAction() = 0;

	Building* getBuilding();
};
