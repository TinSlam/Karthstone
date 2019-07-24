#pragma once

#include "Mewtle.h"

#include "Concepts/Deck.h"
#include "States/BattleState/City.h"
#include "States/BattleState/BuildPhase.h"

class BattleState : public Mewtle::State{

public :
	BattleState();
	~BattleState();

	void init();
	void initCity();
	void initDeck();
	void tick();
	void render();
	void keyboardInput();
	void mouseLeftPressed(double x, double y);
	void mouseLeftReleased(double x, double y);
	void mouseRightPressed(double x, double y);
	void mouseRightReleased(double x, double y);

	void startBuildPhase(BuildingCard* card);
	void endBuildPhase();

	void endTurnOnClick();

	static Deck* deck;
	static City* city;
	static BuildPhase* buildPhase;
};