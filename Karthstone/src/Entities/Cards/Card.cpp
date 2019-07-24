#include <MewtlePrecompiledHeaders.h>

#include "Card.h"

#include "States/BattleState/BattleState.h"

Card::Card(int id, std::string name, int textureId) : Label(id, Mewtle::Texture::getTexture(textureId), 0, 0, 0, 0, 0){

}

Card::~Card(){

}

void Card::draw(){
	if(exhausted) return;
	onDraw();
}

void Card::discard(){
	if(exhausted) return;
	BattleState* state = (BattleState*) Mewtle::Game::state;
	state->deck->discard(this);
	onDiscard();
}

void Card::play(){
	if(exhausted) return;
	onPlay();
	discard();
}

void Card::exhaust(){
	exhausted = true;
	std::vector<Card*>* vector = BattleState::deck->discardPile;
	if(!vector->empty()){
		auto iterator = std::find(vector->begin(), vector->end(), this);
		if(iterator != vector->end()) vector->erase(iterator);
	}
	vector = BattleState::deck->drawPile;
	if(!vector->empty()){
		auto iterator = std::find(vector->begin(), vector->end(), this);
		if(iterator != vector->end()) vector->erase(iterator);
	}
	vector = BattleState::deck->hand;
	if(!vector->empty()){
		auto iterator = std::find(vector->begin(), vector->end(), this);
		if(iterator != vector->end()) vector->erase(iterator);
	}
}

void Card::setCardSlot(CardSlot* cardSlot, int num){
	this->cardSlot = cardSlot;
	this->x = cardSlot->getX(num % 2);
	this->y = cardSlot->getY(num % 2);
	this->width = cardSlot->getWidth();
	this->height = cardSlot->getHeight();
	this->rotZ = cardSlot->getRot(num % 2);
	adjustOpenGLCoords();
}

CardSlot* Card::getCardSlot(){
	return cardSlot;
}
