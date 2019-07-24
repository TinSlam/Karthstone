#include <MewtlePrecompiledHeaders.h>

#include "NPC.h"

#include "States/BattleState/BattleState.h"

std::vector<NPC*> NPC::npcs;

NPC::NPC(int id, Mewtle::Model3D* model, Mewtle::Texture* texture, int x, int y, int width, int height, int depth)
	: Entity(id, model, texture,
		BattleState::city->getMapX() + x * BattleState::city->getGridWidth(), 
		BattleState::city->getMapY() + y * BattleState::city->getGridHeight(),
		0, rotX, rotY, rotZ,
		(float) width * BattleState::city->getGridWidth(),
		(float) height * BattleState::city->getGridHeight(), (float) depth){

	this->tileX = x;
	this->tileY = y;

	city = BattleState::city;
	target = city->getCastle();

	endTurn();

	city->positionEntity(this, x - (float) (width - 1) / 2, y - (float) (height - 1) / 2);
	adjustRotation();

	npcs.push_back(this);
}

NPC::~NPC(){
	
}

void NPC::onEndTurn(){
	for(std::vector<NPC*>::iterator it = npcs.begin(); it != npcs.end(); it++){
		(*it)->startTurn();
		(*it)->performIntent();
		(*it)->endTurn();
	}
}

void NPC::renderAll(){
	for(std::vector<NPC*>::iterator it = npcs.begin(); it != npcs.end(); it++){
		(*it)->renderTrail();
		(*it)->render();
	}
}

void NPC::reAdjustMovements(){
	for(std::vector<NPC*>::iterator it = npcs.begin(); it != npcs.end(); it++){
		if((*it)->intent == INTENT::MOVE)
			(*it)->choosePosition();
	}
}

void NPC::adjustRotation(){
	int tile[2];
	city->getTileFromWorldCoordinate(target->getX() + target->getWidth() / 2,
		target->getY() + target->getHeight() / 2,
		tile);
	
	setRotation(0, 0, (float) Mewtle::Utils::atan(-(float) (tileY - tile[1]), (float) tileX - (float) tile[0]) + (float) Mewtle::Utils::getPI() / 2);
}

void NPC::startTurn(){
	
}

void NPC::performIntent(){
	switch(intent){
		case INTENT::ATTACK :
			attack(target);
			break;

		case INTENT::MOVE :
			move(newPositionX, newPositionY);
			break;

		case INTENT::BUFF :
			buff();
			break;

		case INTENT::DEBUFF :
			debuff();
			break;

		case INTENT::SPECIAL :
			special();
			break;
	}
}

void NPC::endTurn(){
	chooseIntent();
	switch(intent){
		case INTENT::ATTACK :
			chooseTarget();
			break;

		case INTENT::MOVE :
			choosePosition();
			break;

		case INTENT::BUFF :
			chooseBuff();
			break;

		case INTENT::DEBUFF :
			chooseDebuff();
			break;

		case INTENT::SPECIAL :
			chooseSpecial();
			break;
	}
}

void NPC::chooseIntent(){
	intent = INTENT::MOVE;
}

void NPC::chooseTarget(){
	target = city->getCastle();
}

void NPC::choosePosition(){
	std::vector<Mewtle::MapNode*> path;
	city->findPath(tileX, tileY, city->getCastle(), 1, 1, &path);
	if(!path.empty()){
		int steps = Mewtle::Utils::min(this->steps, (int) path.size() - 1);
		if(this->path != nullptr){
			for(auto it = (this->path)->begin(); it != (this->path)->end(); it++){
				delete(*it);
			}
			delete(this->path);
		}
		this->path = new std::vector<Mewtle::MapNode*>();
		for(int i = 1; i < steps + 1; i++){
			this->path->push_back(new Mewtle::MapNode(path[i]->getX() + 1, path[i]->getY() + 1));
		}
		newPositionX = path[steps]->getX() + 1;
		newPositionY = path[steps]->getY() + 1;
	}else{
		newPositionX = tileX;
		newPositionY = tileY;
	}
	for(auto it = path.begin(); it != path.end(); it++){
		delete *it;
	}
}

void NPC::chooseBuff(){

}

void NPC::chooseDebuff(){

}

void NPC::chooseSpecial(){

}

void NPC::attack(Entity* target){

}

void NPC::move(int newTileX, int newTileY){
	tileX = newTileX;
	tileY = newTileY;
	city->positionEntity(this, (float) tileX, (float) tileY);
	target = city->getCastle();
	adjustRotation();
}

void NPC::buff(){

}

void NPC::debuff(){

}

void NPC::special(){

}

void NPC::renderTrail(){
	float depth = 0;
	int lastX = tileX;
	int lastY = tileY;
	for(auto it = path->begin(); it != path->end(); it++, depth += 0.001f){
		Mewtle::MapNode* node = *it;
		city->drawTrail(node->getX(), node->getY(), lastX, lastY, depth);
		lastX = node->getX();
		lastY = node->getY();
	}
}
