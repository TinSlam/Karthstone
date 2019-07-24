#pragma once

class ResourceManager{
public :
	static void loadModels();
	static void loadTextures();

	static int MODEL_SQUARE;
	static int MODEL_CUBE;

	static int TEXTURE_TEST_CIRCLE;
	static int TEXTURE_CITY_BACKGROUND;
	static int TEXTURE_CITY_GRID;
	static int TEXTURE_DRAW_PILE;
	static int TEXTURE_DISCARD_PILE;
	static int TEXTURE_END_TURN_BUTTON;
	static int TEXTURE_END_TURN_BUTTON_HOVER;

	static int TEXTURE_CARD_WALL;

	static int TEXTURE_MONSTER_1;

	static int TEXTURE_TRAIL_SEGMENT;
	static int TEXTURE_TRAIL_ARROW;

	static int* TEXTURE_TILES;
};
