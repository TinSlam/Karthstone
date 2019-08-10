#include <MewtlePrecompiledHeaders.h>

#include "ResourceManager.h"

#include "Mewtle.h"

int ResourceManager::MODEL_SQUARE;
int ResourceManager::MODEL_CUBE;

int ResourceManager::TEXTURE_TEST_CIRCLE;
int ResourceManager::TEXTURE_CITY_BACKGROUND;
int ResourceManager::TEXTURE_CITY_GRID;
int ResourceManager::TEXTURE_DRAW_PILE;
int ResourceManager::TEXTURE_DISCARD_PILE;
int ResourceManager::TEXTURE_END_TURN_BUTTON;
int ResourceManager::TEXTURE_END_TURN_BUTTON_HOVER;

int ResourceManager::TEXTURE_CARD_WALL;

int ResourceManager::TEXTURE_MONSTER_1;

int ResourceManager::TEXTURE_TRAIL_SEGMENT;
int ResourceManager::TEXTURE_TRAIL_ARROW;

int* ResourceManager::TEXTURE_TILES = new int[9];

void ResourceManager::loadModels(){
	//MODEL_SQUARE = Mewtle::Game::createModel("assets/models/Premade/square.obj");
	//MODEL_CUBE = Mewtle::Game::createModel("assets/models/Premade/block.obj");
	MODEL_CUBE = Mewtle::Game::createModel("assets/models/random_model.obj");
}

void ResourceManager::loadTextures(){
	TEXTURE_TEST_CIRCLE = Mewtle::Game::createTexture("assets/textures/test_circle.png");
	TEXTURE_CITY_BACKGROUND = Mewtle::Game::createTexture("assets/textures/city_background.png");
	TEXTURE_CITY_GRID = Mewtle::Game::createTexture("assets/textures/color_black.png");
	TEXTURE_DRAW_PILE = Mewtle::Game::createTexture("assets/textures/card1.png");
	TEXTURE_DISCARD_PILE = Mewtle::Game::createTexture("assets/textures/card2.png");
	TEXTURE_END_TURN_BUTTON = Mewtle::Game::createTexture("assets/textures/end_turn_button.png");
	TEXTURE_END_TURN_BUTTON_HOVER = Mewtle::Game::createTexture("assets/textures/end_turn_button_hover.png");

	TEXTURE_CARD_WALL = Mewtle::Game::createTexture("assets/textures/card_wall.png");

	TEXTURE_MONSTER_1 = Mewtle::Game::createTexture("assets/textures/monster1.png");

	TEXTURE_TRAIL_SEGMENT = Mewtle::Game::createTexture("assets/textures/trail_segment.png");
	TEXTURE_TRAIL_ARROW = Mewtle::Game::createTexture("assets/textures/monster1.png");

	for(int i = 0; i < 9; i++){
		std::string path = "assets/textures/mario_8bit_";
		path.append(std::to_string(i));
		path.append(".png");
		TEXTURE_TILES[i] = Mewtle::Game::createTexture(path.c_str());
	}
}
