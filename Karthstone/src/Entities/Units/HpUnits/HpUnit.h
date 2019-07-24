#pragma once

#include "Mewtle.h"

class HpUnit : public Mewtle::Entity{
	int maxHp;
	int hp;

public:
	HpUnit(int id, Mewtle::Model3D* model, Mewtle::Texture* texture, float x, float y, float z, float rotX, float rotY, float rotZ, float width, float height, float depth, int maxHp);
	~HpUnit();

	int getMaxHp();
	int getHp();
	void setMaxHp(int value);
	void setHp(int value);
	void damage(int value);
};