#include <MewtlePreCompiledHeaders.h> // Add this line at the beginning of every cpp file.

#include "Mewtle.h" // The engine interface.

#include <Mewtle/Core/EntryPoint.h>

#include "States/BattleState/BattleState.h"
#include "ResourceManager/ResourceManager.h"

Mewtle::State* Mewtle::createInitialState(){
	// Return your initial state.
	return new BattleState();
}

void Mewtle::init(){
	CardSlot::init();
}

void Mewtle::loadModels(){
	ResourceManager::loadModels();
}

void Mewtle::loadTextures(){
	ResourceManager::loadTextures();
}

void Mewtle::tick(){

}

void Mewtle::render(){

}