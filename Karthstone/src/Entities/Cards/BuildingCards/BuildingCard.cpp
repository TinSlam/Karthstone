#include <MewtlePrecompiledHeaders.h>

#include "BuildingCard.h"

#include "Entities/Buildings/Building.h"
#include "States/BattleState/BattleState.h"
#include "States/BattleState/City.h"

BuildingCard::BuildingCard(int id, std::string name, int textureId, Building* building) : Card(id, name, textureId){
	this->building = building;
}

BuildingCard::~BuildingCard(){
	delete(building);
}

void BuildingCard::onPlay(){
	BattleState* state = (BattleState*) Mewtle::Game::state;
	building->position(state->city, 6, 7, City::ROTATION::ZERO);
	exhaust();
}

Building* BuildingCard::getBuilding(){
	return building;
}
