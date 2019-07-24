#pragma once

#include "Mewtle.h"

#include "Concepts/CardSlot.h"

class Card : public Mewtle::Label{
public :
	enum Place{DRAW_PILE, HAND, DISCARD_PILE};
	static std::vector<Card> cards;

private :
	std::string name;
	Place place = HAND;
	CardSlot* cardSlot;
	bool exhausted = false;

public :
	Card(int id, std::string name, int textureId);
	~Card();

	void play();
	void draw();
	void discard();
	void exhaust();

	void setCardSlot(CardSlot*, int);
	CardSlot* getCardSlot();

	virtual void onClick() = 0;
	virtual void onPlay() = 0;
	virtual void onDraw() = 0;
	virtual void onDiscard() = 0;
	virtual void endTurnAction() = 0;
	virtual void startTurnAction() = 0;
};
