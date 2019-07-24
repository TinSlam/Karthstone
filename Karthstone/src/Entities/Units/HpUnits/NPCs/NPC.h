#pragma once

#include "Mewtle.h"

#include "States/BattleState/City.h"

class NPC : public Mewtle::Entity{
public :
	enum INTENT {ATTACK, BUFF, DEBUFF, SPECIAL, MOVE};

private :
	int tileX, tileY;
	INTENT intent;
	City* city = nullptr;
	Mewtle::Entity* target = nullptr;
	int newPositionX, newPositionY;
	int steps = 8;
	std::vector<Mewtle::MapNode*>* path = nullptr;

	static std::vector<NPC*> npcs;

	void adjustRotation();

public:
	NPC(int id, Mewtle::Model3D* model, Mewtle::Texture* texture, int x, int y, int width, int height, int depth);
	~NPC();

	void endTurn();
	void startTurn();
	void performIntent();
	void move(int newTileX, int newTileY);
	void attack(Mewtle::Entity* target);
	void buff();
	void debuff();
	void special();

	void chooseIntent();
	void chooseTarget();
	void choosePosition();
	void chooseBuff();
	void chooseDebuff();
	void chooseSpecial();

	void renderTrail();

	static void onEndTurn();
	static void renderAll();
	static void reAdjustMovements();
};
