#include <MewtlePrecompiledHeaders.h>

#include "BuildPhase.h"

#include "Entities/Cards/BuildingCards/BuildingCard.h"
#include "States/BattleState/City.h"
#include "ResourceManager/ResourceManager.h"
#include "Utils/GameUtils.h"
#include "Entities/Units/HpUnits/NPCs/NPC.h"

BuildPhase::BuildPhase(BuildingCard* card, City* city){
	this->card = card;
	this->city = city;

	int id = Mewtle::Game::createLabel(Mewtle::Texture::getTexture(ResourceManager::TEXTURE_CITY_GRID), 0, 0, (float) Mewtle::Game::width, (float) Mewtle::Game::height, 0);
	greyScreen = (Mewtle::Label*) Mewtle::Game::getEntity(id);

	id = Mewtle::Game::createEntity(card->getBuilding()->getModel(), Mewtle::Texture::getTexture(card->getBuilding()->getTextureId()), 0, 0, 0, 0, 0, 0, 100, 100, 100);
	prototypeBuilding = Mewtle::Game::getEntity(id);
}

BuildPhase::~BuildPhase(){
	delete(greyScreen);
	delete(prototypeBuilding);
}

void BuildPhase::start(){
	
}

void BuildPhase::tick(){
	int tile[2];
	city->getTile(Mewtle::Game::getMouseX(), Mewtle::Game::getMouseY(), tile);
	city->alignToGrid(tile[0], tile[1], card->getBuilding()->getTileWidth(), card->getBuilding()->getTileHeight(), rotation, prototypeBuilding, card->getBuilding()->getDepth());
}

void BuildPhase::render(){
	greyScreen->render(0.3f);
	prototypeBuilding->render(0.6f);
}

void BuildPhase::end(){
	GameUtils::getBattleState()->endBuildPhase();
	delete(this);
}

bool BuildPhase::mouseLeftReleased(double x, double y){
	int tile[2];
	city->getTile(x, y, tile);
	int tileX = tile[0];
	int tileY = tile[1];
	if(city->alignToGrid(tileX, tileY, card->getBuilding()->getTileWidth(), card->getBuilding()->getTileHeight(), rotation, card->getBuilding(), card->getBuilding()->getDepth())){
		card->play();
		card->getBuilding()->position(city, tileX, tileY, rotation);
		NPC::reAdjustMovements();
	}
	end();
	return true;
}

bool BuildPhase::mouseRightReleased(double x, double y){
	end();
	return true;
}

bool BuildPhase::keyboardInput(){
	if(Mewtle::Game::keyReleased(GLFW_KEY_LEFT_CONTROL)){
		switch(rotation){
			case City::ROTATION::ZERO :
				rotation = City::ROTATION::TWO_SEVENTY;
				break;

			case City::ROTATION::NINETY :
				rotation = City::ROTATION::ZERO;
				break;

			case City::ROTATION::ONE_EIGHTY :
				rotation = City::ROTATION::NINETY;
				break;

			case City::ROTATION::TWO_SEVENTY :
				rotation = City::ROTATION::ONE_EIGHTY;
				break;
		}
	}
	if(Mewtle::Game::keyReleased(GLFW_KEY_RIGHT_CONTROL)){
		switch(rotation){
			case City::ROTATION::ZERO :
				rotation = City::ROTATION::NINETY;
				break;

			case City::ROTATION::NINETY :
				rotation = City::ROTATION::ONE_EIGHTY;
				break;

			case City::ROTATION::ONE_EIGHTY :
				rotation = City::ROTATION::TWO_SEVENTY;
				break;

			case City::ROTATION::TWO_SEVENTY :
				rotation = City::ROTATION::ZERO;
				break;
		}
	}
	return true;
}
