#include <MewtlePrecompiledHeaders.h>

#include "City.h"

#include "ResourceManager/ResourceManager.h"
#include "Mewtle/ResourceManager/Model/ModelPremade.h"
#include "Entities/Buildings/Building.h"
#include "Entities/Units/HpUnits/NPCs/NPC.h"

City::City(int width, int height){
	this->width = width;
	this->height = height;
}


City::~City(){
	delete(background);
	for(auto it = grid.begin(); it != grid.end(); it++){
		delete(*it);
	}
}

void City::init(){
	initializeMap();

	mapWidth = (float) Mewtle::Game::height;
	mapHeight = (float) Mewtle::Game::height;
	float mapXOffset = -mapWidth / 2;
	float mapYOffset = -mapHeight / 2;
	int gridWidth = width;
	int gridHeight = height;
	float gridHorGap = mapWidth / gridWidth;
	float gridVerGap = mapHeight / gridHeight;
	float gridSize = 2;

	centerVector = glm::vec3(-gridHorGap / 2, -gridVerGap / 2, 0);
	this->gridWidth = gridHorGap;
	this->gridHeight = gridVerGap;

	int backgroundId = Mewtle::Game::createEntity(Mewtle::Model3D::getModel(ResourceManager::MODEL_CUBE), Mewtle::Texture::getTexture(ResourceManager::TEXTURE_CITY_BACKGROUND), mapXOffset, mapYOffset, -0.0001f, 0, 0, 0, mapWidth, mapHeight, 0.001f);
	std::vector<int> gridId;
	for(int i = 0; i <= gridWidth; i += 1){
		gridId.push_back(Mewtle::Game::createEntity(Mewtle::Model3D::getModel(ResourceManager::MODEL_SQUARE), Mewtle::Texture::getTexture(ResourceManager::TEXTURE_CITY_GRID), mapXOffset, mapYOffset + i * gridHorGap - gridSize / 2, 0, 0, 0, 0, mapWidth, gridSize, 0));
	}
	for(int i = 0; i <= gridHeight; i += 1){
		gridId.push_back(Mewtle::Game::createEntity(Mewtle::Model3D::getModel(Mewtle::ModelPremade::MODEL_SQUARE), Mewtle::Texture::getTexture(ResourceManager::TEXTURE_CITY_GRID), mapXOffset + i * gridVerGap - gridSize / 2, mapYOffset, 0, 0, 0, 0, gridSize, mapHeight, 0));
	}
	background = Mewtle::Game::getEntity(backgroundId);
	for(int i = 0; i < gridWidth + gridHeight + 2; i++){
		grid.push_back(Mewtle::Game::getEntity(gridId[i]));
	}

	castle = new Building(Mewtle::Game::generateId(), Mewtle::Model3D::getModel(ResourceManager::MODEL_CUBE), Mewtle::Texture::getTexture(ResourceManager::TEXTURE_CITY_GRID), 1, 1, 150);
	castle->position(this, 6, 6, City::ROTATION::ZERO);

	Building* b1 = new Building(Mewtle::Game::generateId(), Mewtle::Model3D::getModel(ResourceManager::MODEL_CUBE), Mewtle::Texture::getTexture(ResourceManager::TEXTURE_DRAW_PILE), 3, 1, 150);
	Building* b2 = new Building(Mewtle::Game::generateId(), Mewtle::Model3D::getModel(ResourceManager::MODEL_CUBE), Mewtle::Texture::getTexture(ResourceManager::TEXTURE_DISCARD_PILE), 2, 3, 100);
	Building* b3 = new Building(Mewtle::Game::generateId(), Mewtle::Model3D::getModel(ResourceManager::MODEL_CUBE), Mewtle::Texture::getTexture(ResourceManager::TEXTURE_TEST_CIRCLE), 1, 1, 66);
	b1->position(this, 3, 3, City::ROTATION::ZERO);
	b2->position(this, 7, 9, City::ROTATION::ZERO);
	b3->position(this, 4, 6, City::ROTATION::ZERO);
}

void City::findPath(int x, int y, int targetX, int targetY, int xClearance, int yClearance, std::vector<Mewtle::MapNode*>* path){
	Mewtle::AI::aStar(x - 1, y - 1, targetX - 1, targetY - 1, xClearance, yClearance, this->xClearance, this->yClearance, width, height, path, false);
}

void City::findPath(int x, int y, Mewtle::Entity* target, int xClearance, int yClearance, std::vector<Mewtle::MapNode*>* path){
	int tile[2];
	getTileFromWorldCoordinate(target->getX(), target->getY(), tile);
	Mewtle::AI::aStarTarget(x - 1, y - 1, tile[0], tile[1], xClearance, yClearance, this->xClearance, this->yClearance, width, height, path, false);
}

void City::initializeMap(){
	const int size = width * height;
	rawMap = new int[size];
	xClearance = new int[size];
	yClearance = new int[size];

	for(int i = 0; i < size; i++){
		*(rawMap + i) = 0;
	}

	Mewtle::AI::initializeClearanceValues(rawMap, width, height, xClearance, yClearance);
}

void City::updateMap(Building* building, int oldX, int oldY, int newX, int newY, ROTATION oldRotation, ROTATION rotation){
	int convertedCoords[2];
	if(oldX != -1 && oldY != -1){
		for(int i = 0; i < building->getTileWidth(); i++){
			for(int j = 0; j < building->getTileHeight(); j++){
				rotatedCoords(oldX + i, oldY + j, oldX, oldY, oldRotation, convertedCoords);
				Mewtle::AI::updateMap(convertedCoords[0] - 1, convertedCoords[1] - 1, 0, xClearance, yClearance, rawMap, width, height);
			}
		}
	}
	for(int i = 0; i < building->getTileWidth(); i++){
		for(int j = 0; j < building->getTileHeight(); j++){
			rotatedCoords(newX + i, newY + j, newX, newY, rotation, convertedCoords);
			Mewtle::AI::updateMap(convertedCoords[0] - 1, convertedCoords[1] - 1, 1, xClearance, yClearance, rawMap, width, height);
		}
	}
	/*for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			std::cout << *(xClearance + j * height + i) << ", ";
		}
		std::cout << std::endl;
	}*/
}

void City::rotatedCoords(int x, int y, int xOrig, int yOrig, ROTATION rotation, int* converted){
	switch(rotation){
		case ZERO :
			converted[0] = x;
			converted[1] = y;
			break;

		case ONE_EIGHTY :
			converted[0] = 2 * xOrig - x;
			converted[1] = 2 * yOrig - y;
			break;

		case NINETY:
			converted[0] = xOrig + (y - yOrig) - 1;
			converted[1] = yOrig + (x - xOrig);
			break;

		case TWO_SEVENTY:
			converted[0] = xOrig + (yOrig - y) + 1;
			converted[1] = yOrig + (xOrig - x);
			break;

		default :
			converted[0] = x;
			converted[1] = y;
	}
}

void City::render(){
	renderBackground();
	renderGrid();
	castle->render();
}

void City::drawTrail(int x1, int y1, int x2, int y2, float level){
	float tile[2];
	getGridPosition(x1, y1, tile);
	float rotZ = 0;
	if(x1 == x2){
		if(y1 > y2){
			rotZ = (float) Mewtle::Utils::getPI() * 3 / 2;
			tile[0] -= gridWidth / 2;
			tile[1] -= gridHeight / 2;
		}else{
			rotZ = (float) Mewtle::Utils::getPI() / 2;
			tile[0] -= gridWidth / 2;
			tile[1] += gridHeight / 2;
		}
	}else{
		if(x1 > x2) tile[0] -= gridWidth;
	}
	int id = Mewtle::Game::createEntity(Mewtle::Model3D::getModel(ResourceManager::MODEL_SQUARE), Mewtle::Texture::getTexture(ResourceManager::TEXTURE_TRAIL_SEGMENT), tile[0], tile[1], level, 0, 0, rotZ, 2 * gridWidth, gridHeight, 1);
	Mewtle::Game::getEntity(id)->render();
	delete Mewtle::Game::getEntity(id);
}

void City::renderBackground(){
	background->render();
}

void City::renderGrid(){
	for(int i = 0; i < width + height + 2; i++){
		grid[i]->render();
	}
}

void City::endTurn(){
	NPC::onEndTurn();
}

void City::getTile(double x, double y, int* tile){
	Mewtle::Line3D* line = new Mewtle::Line3D(0, 0, 0, 1, 1, 1);
	Mewtle::Game::getMouseVector(x, y, line);
	double vector[3];
	line->getLineFromZComponent(0, vector);
	vector[0] = Mewtle::Utils::getOpenGLWidthInPixels(vector[0]);
	vector[1] = Mewtle::Utils::getOpenGLHeightInPixels(vector[1]);
	vector[0] -= getMapX() - getGridWidth() / 2;
	vector[1] -= getMapY() - getGridHeight() / 2;
	int tileX = (int)(vector[0] / getGridWidth());
	int tileY = (int)(vector[1] / getGridHeight());
	tile[0] = tileX;
	tile[1] = tileY;
	delete(line);
}

void City::getGridPosition(int x, int y, float position[]){
	position[0] = getMapX() + x * getGridWidth() - getGridWidth() / 2;
	position[1] = getMapY() + y * getGridHeight() - getGridHeight() / 2;
}

void City::getTileFromWorldCoordinate(float x, float y, int* tile){
	x -= getMapX();
	y -= getMapY();
	tile[0] = (int)(x / gridWidth);
	tile[1] = (int)(y / gridHeight);
}

bool City::alignToGrid(int x, int y, int width, int height, ROTATION rotation, Mewtle::Entity* prototypeBuilding, float depth){
	float buildingPosition[2];
	switch(rotation){
		case ZERO :
			getGridPosition(x, y, buildingPosition);
			prototypeBuilding->setPosition(buildingPosition[0], buildingPosition[1], 0);
			prototypeBuilding->setSize(width * getGridWidth(),
				height * getGridHeight(),
				depth);
			// TODO : These should check for free tiles.
			if(x <= 0 || x + width > this->width + 1 ||
				y <= 0 || y + height > this->height + 1) return false;
			break;

		case NINETY :
			getGridPosition(x - height + 1, y, buildingPosition);
			prototypeBuilding->setPosition(buildingPosition[0], buildingPosition[1], 0);
			prototypeBuilding->setSize(height * getGridWidth(),
				width * getGridHeight(),
				depth);
			if(x - height + 1 <= 0 || x + 1 > this->height + 1 ||
				y <= 0 || y + width > this->width + 1) return false;
			break;

		case ONE_EIGHTY :
			getGridPosition(x - width + 1, y - height + 1, buildingPosition);
			prototypeBuilding->setPosition(buildingPosition[0], buildingPosition[1], 0);
			prototypeBuilding->setSize(width * getGridWidth(),
				height * getGridHeight(),
				depth);
			if(x - width + 1 <= 0 || x + 1 > this->width + 1 ||
				y - height + 1 <= 0 || y + 1 > this->height + 1) return false;
			break;

		case TWO_SEVENTY :
			getGridPosition(x, y - width + 1, buildingPosition);
			prototypeBuilding->setPosition(buildingPosition[0], buildingPosition[1], 0);
			prototypeBuilding->setSize(height * getGridWidth(),
				width * getGridHeight(),
				depth);
			if(x <= 0 || x + height > this->height + 1 ||
				y - width + 1 <= 0 || y + 1 > this->width + 1) return false;
			break;
	}
	return true;
}

void City::positionEntity(Mewtle::Entity* entity, float x, float y){
	entity->setPosition(getMapX() + x * gridWidth - gridWidth / 2,
		getMapY() + y * gridHeight - gridHeight / 2,
		0);
}

bool City::mouseLeftPressed(double x, double y){
	return background->mouseOver(x, y);
}

bool City::mouseLeftReleased(double x, double y){
	return false;
}

bool City::mouseRightPressed(double x, double y){
	return false;
}

bool City::mouseRightReleased(double x, double y){
	return false;
}

float City::getMapX(){
	return centerVector.x - mapWidth / 2;
}

float City::getMapY()
{
	return centerVector.y - mapHeight / 2;
}

float City::getMapWidth(){
	return mapWidth;
}

float City::getMapHeight(){
	return mapHeight;
}

float City::getGridWidth(){
	return gridWidth;
}

float City::getGridHeight(){
	return gridHeight;
}

int City::getWidth(){
	return width;
}

int City::getHeight(){
	return height;
}

glm::vec3 City::getCenterVector(){
	return centerVector;
}

Building* City::getCastle(){
	return castle;
}
