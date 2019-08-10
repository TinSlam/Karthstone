#include <MewtlePrecompiledHeaders.h>

#include "Mewtle.h"

#include "CardSlot.h"


CardSlot CardSlot::handSlots[10] = {
	CardSlot(0.0f, 1.0f, 0.0f, 1.0f, 0.1f, 0.1f, 0.0f, 0.0f),
	CardSlot(0.0f, 1.0f, 0.0f, 1.0f, 0.1f, 0.1f, 0.0f, 0.0f),
	CardSlot(0.0f, 1.0f, 0.0f, 1.0f, 0.1f, 0.1f, 0.0f, 0.0f),
	CardSlot(0.0f, 1.0f, 0.0f, 1.0f, 0.1f, 0.1f, 0.0f, 0.0f),
	CardSlot(0.0f, 1.0f, 0.0f, 1.0f, 0.1f, 0.1f, 0.0f, 0.0f),
	CardSlot(0.0f, 1.0f, 0.0f, 1.0f, 0.1f, 0.1f, 0.0f, 0.0f),
	CardSlot(0.0f, 1.0f, 0.0f, 1.0f, 0.1f, 0.1f, 0.0f, 0.0f),
	CardSlot(0.0f, 1.0f, 0.0f, 1.0f, 0.1f, 0.1f, 0.0f, 0.0f),
	CardSlot(0.0f, 1.0f, 0.0f, 1.0f, 0.1f, 0.1f, 0.0f, 0.0f),
	CardSlot(0.0f, 1.0f, 0.0f, 1.0f, 0.1f, 0.1f, 0.0f, 0.0f)
};
CardSlot CardSlot::drawPileSlot = CardSlot(0, (float) Mewtle::Game::height - 300, 0, (float) Mewtle::Game::height - 300, 200, 300, 0, 0);
CardSlot CardSlot::discardPileSlot = CardSlot((float) Mewtle::Game::width - 200, (float) Mewtle::Game::height - 300, (float) Mewtle::Game::width - 200, (float) Mewtle::Game::height - 300, 200, 300, 0, 0);

CardSlot::CardSlot(float x1, float y1, float x2, float y2, float width, float height, float rot1, float rot2){
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->width = width;
	this->height = height;
	this->rot1 = rot1;
	this->rot2 = rot2;
}

CardSlot::~CardSlot(){

}

void CardSlot::init(){
	drawPileSlot = CardSlot(0, (float) Mewtle::Game::height - 300, 0, (float) Mewtle::Game::height - 300, 200, 300, 0, 0);
	discardPileSlot = CardSlot((float) Mewtle::Game::width - 200, (float) Mewtle::Game::height - 300, (float) Mewtle::Game::width - 200, (float) Mewtle::Game::height - 300, 200, 300, 0, 0);
}

void CardSlot::initSlots(int cardNum){
	float width = 150;
	float height = 300;
	float scale = (10 - cardNum) * 10.0f;
	width += 1.3f * scale;
	height += scale;
	float xOffset = (Mewtle::Game::width - cardNum * width) / 2;
	float yOffset = Mewtle::Game::height - height;
	for(int i = 0; i < (cardNum % 2 == 0 ? cardNum + 1 : cardNum); i++){
		CardSlot* cardSlot = &handSlots[i];
		cardSlot->x2 = xOffset + width * i - Mewtle::Utils::convertHeightToOpenGL(50 * height * (i - cardNum / 2));
		cardSlot->y2 = yOffset + Mewtle::Utils::convertHeightToOpenGL(25 * height * abs((i - cardNum / 2)));
		cardSlot->rot2 = (float) -M_PI * (i - cardNum / 2) / 96;
		cardSlot->width = width;
		cardSlot->height = height;
		if(i < cardNum / 2){
			cardSlot->x1 = xOffset + width * i - Mewtle::Utils::convertWidthToOpenGL(50 * height * (i - cardNum / 2));
			cardSlot->y1 = yOffset + Mewtle::Utils::convertHeightToOpenGL(25 * height * abs((i - cardNum / 2)));
			cardSlot->rot1 = (float) -M_PI * (i - cardNum / 2) / 96;
		}else{
			if(i == cardNum / 2) continue;
			cardSlot--;
			cardSlot->x1 = xOffset + width * (i - 1) - Mewtle::Utils::convertWidthToOpenGL(50 * height * ((i - 1) - cardNum / 2));
			cardSlot->y1 = yOffset + Mewtle::Utils::convertHeightToOpenGL(25 * height * abs((i - cardNum / 2)));
			cardSlot->rot1 = (float) -M_PI * (i - cardNum / 2) / 96;
		}
	}
}

float CardSlot::getX(int handSize){
	switch(handSize){
		case 0 :
			return x1;
			break;

		case 1 :
			return x2;
			break;

		default :
			return 0;
	}
}

float CardSlot::getY(int handSize){
	switch(handSize){
		case 0 :
			return y1;
			break;

		case 1 :
			return y2;
			break;

		default :
			return 0;
	}
}

float CardSlot::getWidth(){
	return width;
}

float CardSlot::getHeight(){
	return height;
}

float CardSlot::getRot(int handSize){
	switch(handSize){
		case 0 :
			return rot1;
			break;

		case 1 :
			return rot2;
			break;

		default :
			return 0;
	}
}
