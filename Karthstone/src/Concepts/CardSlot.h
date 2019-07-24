#pragma once

class CardSlot{
private :
	float x1, y1, x2, y2, width, height, rot1, rot2;

public :
	CardSlot(float, float, float, float, float, float, float, float);
	~CardSlot();

	static void initSlots(int);

	float getX(int);
	float getY(int);
	float getWidth();
	float getHeight();
	float getRot(int);

	static CardSlot handSlots[10];
	static CardSlot drawPileSlot;
	static CardSlot discardPileSlot;
};