#include <MewtlePrecompiledHeaders.h>

#include "CardWall.h"

#include "Entities/Buildings/Building.h"
#include "ResourceManager/ResourceManager.h"
#include "States/BattleState/BattleState.h"

CardWall::CardWall(int id) : BuildingCard(id, "Wall", ResourceManager::TEXTURE_CARD_WALL, new Building(Mewtle::Game::generateId(), Mewtle::Model3D::getModel(ResourceManager::MODEL_CUBE), Mewtle::Texture::getTexture(ResourceManager::TEXTURE_CITY_GRID), 4, 2, 400)){
	
}

CardWall::~CardWall(){

}

void CardWall::onDraw(){

}

void CardWall::onDiscard(){

}

void CardWall::endTurnAction(){

}

void CardWall::startTurnAction(){

}

void CardWall::onPlayBuildingCard(){

}

void CardWall::onClick(){
	BattleState* state = (BattleState*) Mewtle::Game::state;
	state->startBuildPhase(this);
}
