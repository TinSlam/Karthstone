#pragma once

#include "Mewtle.h"

#include "States/BattleState/City.h"

class Building : public Mewtle::Entity{
	static std::vector<Building*> buildings;

	int tileX = -1, tileY = -1;
	int tileWidth, tileHeight;
	bool placed = false;
	City::ROTATION rotation = City::ROTATION::ZERO;

public :
	Building(int id, Mewtle::Model3D* model, Mewtle::Texture* texture, int tileWidth, int tileHeight, float depth);
	~Building();

	void position(City* city, int x, int y, City::ROTATION rotation);
	void demolish();
	void attacked();

	void setPlaced(bool value);
	bool isPlaced();

	static void renderAllPlaced();

	int getTileWidth();
	int getTileHeight();
	int getTileX();
	int getTileY();
};
