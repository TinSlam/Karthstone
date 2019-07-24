#include <MewtlePrecompiledHeaders.h>

#include "Deck.h"

#include "ResourceManager/ResourceManager.h"
#include "CardSlot.h"
#include "States/BattleState/BattleState.h"

Deck::Deck(std::vector<Card*>* cards){
	this->cards = cards;
	hand = new std::vector<Card*>();
	drawPile = new std::vector<Card*>();
	discardPile = new std::vector<Card*>();

	drawPileTexture = ResourceManager::TEXTURE_DRAW_PILE;
	discardPileTexture = ResourceManager::TEXTURE_DISCARD_PILE;

	drawPileLabelId = Mewtle::Game::createLabel(Mewtle::Texture::getTexture(drawPileTexture), CardSlot::drawPileSlot.getX(1), CardSlot::drawPileSlot.getY(1), CardSlot::drawPileSlot.getWidth(), CardSlot::drawPileSlot.getHeight(), CardSlot::drawPileSlot.getRot(1));
	discardPileLabelId = Mewtle::Game::createLabel(Mewtle::Texture::getTexture(discardPileTexture), CardSlot::discardPileSlot.getX(1), CardSlot::discardPileSlot.getY(1), CardSlot::discardPileSlot.getWidth(), CardSlot::discardPileSlot.getHeight(), CardSlot::discardPileSlot.getRot(1));

	int drawPileTextboxId = Mewtle::Game::createTextbox("Draw 0", CardSlot::drawPileSlot.getX(1),
		CardSlot::drawPileSlot.getY(1),
		CardSlot::drawPileSlot.getX(1) + CardSlot::drawPileSlot.getWidth(),
		CardSlot::drawPileSlot.getY(1) + CardSlot::drawPileSlot.getHeight(),
		36,
		0.0f, 0.0f, 0.0f,
		Mewtle::Textbox::ALIGNMENT::CENTER,
		false, true);

	int discardPileTextboxId = Mewtle::Game::createTextbox("Discard 0", CardSlot::discardPileSlot.getX(1),
		CardSlot::discardPileSlot.getY(1),
		CardSlot::discardPileSlot.getX(1) + CardSlot::discardPileSlot.getWidth(),
		CardSlot::discardPileSlot.getY(1) + CardSlot::discardPileSlot.getHeight(),
		36,
		0.0f, 0.0f, 0.0f,
		Mewtle::Textbox::ALIGNMENT::CENTER,
		false, true);

	drawPileTextbox = (Mewtle::Textbox*) Mewtle::Game::getGUIElement(drawPileTextboxId);
	discardPileTextbox = (Mewtle::Textbox*) Mewtle::Game::getGUIElement(discardPileTextboxId);

	new Mewtle::ButtonRectangle(Mewtle::Game::generateId(),
		Mewtle::Texture::getTexture(ResourceManager::TEXTURE_END_TURN_BUTTON),
		Mewtle::Texture::getTexture(ResourceManager::TEXTURE_END_TURN_BUTTON_HOVER),
		(int) CardSlot::discardPileSlot.getX(1) + (int) CardSlot::discardPileSlot.getWidth() / 6,
		(int) CardSlot::discardPileSlot.getY(1) - (int) CardSlot::discardPileSlot.getHeight() / 3,
		(int) CardSlot::discardPileSlot.getWidth() * 2 / 3,
		(int) CardSlot::discardPileSlot.getHeight() / 4,
		[this](){endTurn();}
	);
}

Deck::~Deck(){
	delete(drawPile);
	delete(discardPile);
	delete(hand);
	for(std::vector<Card*>::iterator it = cards->begin(); it != cards->end(); it++){
		delete(*it);
	}
	delete(cards);

	delete(drawPileTextbox);
	delete(discardPileTextbox);
	delete(Mewtle::Game::getEntity(drawPileLabelId));
	delete(Mewtle::Game::getEntity(discardPileLabelId));
}

void Deck::endTurn(){
	discardHand();
	BattleState::city->endTurn();
	//EventHandler::queueEvent([this](){
		//shuffleDeck();
		//draw(3);
	//});
}

void Deck::init(){
	for(auto it = cards->begin(); it != cards->end(); it++){
		discardPile->push_back(*it);
	}
	shuffleDeck();
}

void Deck::clear(){
	drawPile->clear();
	discardPile->clear();
	hand->clear();
}

void Deck::draw(int number){
	for(int i = 0; i < number; i++){
		if(drawPile->empty()){
			if(discardPile->empty()) return;
			shuffleDeck();
		}
		hand->push_back((*drawPile)[0]);
		drawPile->erase(drawPile->begin());
		drawPileTextbox->setText("Draw " + std::to_string(drawPile->size()));
	}
}

void Deck::discard(Card* card){
	// Look for the card in hand.
	for(size_t i = 0; i < hand->size(); i++){
		if(card == (*hand)[i]){
			discardPile->push_back(card);
			hand->erase(hand->begin() + i);
			discardPileTextbox->setText("Discard " + std::to_string(discardPile->size()));
			return;
		}
	}
	// Look for the card in draw pile.
	for(size_t i = 0; i < drawPile->size(); i++){
		if(card == (*drawPile)[i]){
			discardPile->push_back(card);
			drawPile->erase(drawPile->begin() + i);
			discardPileTextbox->setText("Discard " + std::to_string(discardPile->size()));
			drawPileTextbox->setText("Draw " + std::to_string(drawPile->size()));
			return;
		}
	}
}

void Deck::discardHand(){
	for(std::vector<Card*>::iterator it = hand->begin(); it != hand->end(); it++){
		Card* card = *it;
		//EventHandler::queueEvent([this, card](){discard(card);});
	}
}

void Deck::shuffleDeck(){
	srand((unsigned int) time(NULL));
	while(!discardPile->empty()){
		int index = rand() % discardPile->size();
		drawPile->push_back((*discardPile)[index]);
		discardPile->erase(discardPile->begin() + index);
		discardPileTextbox->setText("Discard " + std::to_string(discardPile->size()));
		drawPileTextbox->setText("Draw " + std::to_string(drawPile->size()));
	}
}

void Deck::render(){
	renderDrawPile();
	renderDiscardPile();
	renderHand();
}

void Deck::renderHand(){
	CardSlot::initSlots((int) hand->size());
	int i = 0;
	for(auto it = hand->begin(); it != hand->end(); it++){
		(*it)->setCardSlot(&CardSlot::handSlots[i], (int) hand->size());
		i++;
		(*it)->render();
	}
}

void Deck::renderDrawPile(){
	Mewtle::Game::getEntity(drawPileLabelId)->render();
	drawPileTextbox->render();
}

void Deck::renderDiscardPile(){
	Mewtle::Game::getEntity(discardPileLabelId)->render();
	discardPileTextbox->render();
}

bool Deck::mouseLeftPressed(double x, double y){
	for(auto it = hand->begin(); it != hand->end(); it++){
		Card* card = *it;
		if(card->mouseOver(x, y)){
			
		}
	}
	return false;
}

bool Deck::mouseLeftReleased(double x, double y){
	for(auto it = hand->begin(); it != hand->end(); it++){
		Card* card = *it;
		if(card->mouseOver(x, y)){
			card->onClick();
			return true;
		}
	}
	return false;
}

bool Deck::mouseRightPressed(double x, double y){
	return false;
}

bool Deck::mouseRightReleased(double x, double y){
	return false;
}