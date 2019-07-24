#pragma once
#include "Entities/Cards/BuildingCards/BuildingCard.h"

class CardWall : public BuildingCard{

public:
	CardWall(int id);
	~CardWall();

	void onClick();
	void onPlayBuildingCard();
	void onDraw();
	void onDiscard();
	void endTurnAction();
	void startTurnAction();
};