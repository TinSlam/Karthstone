#pragma once
#include "Mewtle.h"

class Building;

class City{
private :
	int width;
	int height;

	int backgroundTexture;
	int gridTexture;
	Mewtle::Entity* background;
	std::vector<Mewtle::Entity*> grid;

	glm::vec3 centerVector;
	float mapWidth, mapHeight;
	float gridWidth, gridHeight;

	Building* castle;
	int* rawMap;
	int* xClearance;
	int* yClearance;

	void initializeMap();

public :
	enum ROTATION {ZERO, NINETY, ONE_EIGHTY, TWO_SEVENTY};

	City(int width, int height);
	~City();

	void init();
	void render();
	void renderBackground();
	void renderGrid();
	void drawTrail(int x1, int y1, int x2, int y2, float level);

	void endTurn();

	void getTile(double x, double y, int* tile);
	void getGridPosition(int x, int y, float position[]);
	void getTileFromWorldCoordinate(float x, float y, int* tile);
	bool alignToGrid(int x, int y, int width, int height, ROTATION rotation, Mewtle::Entity* prototypeBuilding, float depth);
	void positionEntity(Mewtle::Entity* entity, float x, float y);
	void rotatedCoords(int x, int y, int xOrig, int yOrig, ROTATION rotation, int* converted);
	void updateMap(Building* building, int oldX, int oldY, int newX, int newY, ROTATION oldRotation, ROTATION rotation);
	void findPath(int x, int y, int targetX, int targetY, int xClearance, int yClearance, std::vector<Mewtle::MapNode*>* path);
	void findPath(int x, int y, Mewtle::Entity* target, int xClearance, int yClearance, std::vector<Mewtle::MapNode*>* path);

	bool mouseLeftPressed(double x, double y);
	bool mouseRightPressed(double x, double y);
	bool mouseLeftReleased(double x, double y);
	bool mouseRightReleased(double x, double y);

	float getMapX();
	float getMapY();
	float getMapWidth();
	float getMapHeight();
	float getGridWidth();
	float getGridHeight();
	int getWidth();
	int getHeight();
	glm::vec3 getCenterVector();

	Building* getCastle();
};
