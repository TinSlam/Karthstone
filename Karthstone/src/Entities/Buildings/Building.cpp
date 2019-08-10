#include <MewtlePrecompiledHeaders.h>

#include "Building.h"

std::vector<Building*> Building::buildings;

Building::Building(int id, Mewtle::Model3D* model, Mewtle::Texture* texture, int tileWidth, int tileHeight, float depth) : Entity(id, model, texture, 0, 0, 0, 0, 0, 0, 1, 1, depth){
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	buildings.push_back(this);
}


Building::~Building(){
	std::vector<Building*>::iterator iterator = std::find(buildings.begin(), buildings.end(), this);
	buildings.erase(iterator);
}

void Building::position(City* city, int x, int y, City::ROTATION rotation){
	city->updateMap(this, tileX, tileY, x, y, this->rotation, rotation);
	this->rotation = rotation;
	tileX = x;
	tileY = y;
	setPlaced(city->alignToGrid(x, y, tileWidth, tileHeight, rotation, this, getDepth()));
}

void Building::demolish(){

}

void Building::attacked(){

}

void Building::renderAllPlaced(){
	for(auto it = buildings.begin(); it != buildings.end(); it++){
		if((*it)->isPlaced()){
			(*it)->render();
		}
	}
}

void Building::setPlaced(bool value){
	placed = value;
}

bool Building::isPlaced(){
	return placed;
}

int Building::getTileWidth(){
	return tileWidth;
}

int Building::getTileHeight(){
	return tileHeight;
}

int Building::getTileX(){
	return tileX;
}

int Building::getTileY(){
	return tileY;
}