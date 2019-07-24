#pragma once
#include "Mewtle.h"

#include "Entities/Cards/Card.h"

class Deck{
public :
	Deck(std::vector<Card*>* cards);
	~Deck();

	std::vector<Card*>* cards;
	std::vector<Card*>* hand;
	std::vector<Card*>* drawPile;
	std::vector<Card*>* discardPile;

	int drawPileLabelId;
	int discardPileLabelId;
	int drawPileTexture;
	int discardPileTexture;

	Mewtle::Textbox* drawPileTextbox;
	Mewtle::Textbox* discardPileTextbox;

	void draw(int number);
	void discard(Card* card);
	void discardHand();
	void shuffleDeck();
	void init();
	void clear();
	void endTurn();

	void render();
	void renderHand();
	void renderDrawPile();
	void renderDiscardPile();

	bool mouseLeftPressed(double x, double y);
	bool mouseRightPressed(double x, double y);
	bool mouseLeftReleased(double x, double y);
	bool mouseRightReleased(double x, double y);
};