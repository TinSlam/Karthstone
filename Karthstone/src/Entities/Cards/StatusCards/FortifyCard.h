#pragma once

#include "Entities/Cards/Card.h"

class FortifyCard : public Card{
public :
	FortifyCard(int, std::string, int);
	~FortifyCard();

	void onClick();
	void onPlay();
	void onDraw();
	void onDiscard();
	void startTurnAction();
	void endTurnAction();
};