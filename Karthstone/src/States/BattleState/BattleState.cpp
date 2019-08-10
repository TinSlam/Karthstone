#include <MewtlePrecompiledHeaders.h>

#include "BattleState.h"

#include "ResourceManager/ResourceManager.h"
#include "Entities/Units/HpUnits/NPCs/NPC.h"
#include "Entities/Cards/StatusCards/FortifyCard.h"
#include "Entities/Cards/BuildingCards/Wall/CardWall.h"
#include "Entities/Buildings/Building.h"

Deck* BattleState::deck;
City* BattleState::city;
BuildPhase* BattleState::buildPhase;

BattleState::BattleState(){

}

BattleState::~BattleState(){

}

void BattleState::endTurnOnClick(){
	
}

void BattleState::init(){
	//Game::translateCamera(0, 0, 4);

	initCity();
	initDeck();

	new NPC(Mewtle::Game::generateId(), Mewtle::Model3D::getModel(ResourceManager::MODEL_CUBE), Mewtle::Texture::getTexture(ResourceManager::TEXTURE_MONSTER_1), 6, 0, 1, 1, 400);
	new NPC(Mewtle::Game::generateId(), Mewtle::Model3D::getModel(ResourceManager::MODEL_CUBE), Mewtle::Texture::getTexture(ResourceManager::TEXTURE_MONSTER_1), 12, 6, 1, 1, 400);
	new NPC(Mewtle::Game::generateId(), Mewtle::Model3D::getModel(ResourceManager::MODEL_CUBE), Mewtle::Texture::getTexture(ResourceManager::TEXTURE_MONSTER_1), 6, 12, 1, 1, 400);
	new NPC(Mewtle::Game::generateId(), Mewtle::Model3D::getModel(ResourceManager::MODEL_CUBE), Mewtle::Texture::getTexture(ResourceManager::TEXTURE_MONSTER_1), 0, 6, 1, 1, 400);
}

void BattleState::initCity(){
	city = new City(11, 11);
	city->init();
}

void BattleState::initDeck(){
	std::vector<Card*>* deckCards = new std::vector<Card*>();
	deckCards->push_back(new FortifyCard(Mewtle::Game::generateId(), "First card", ResourceManager::TEXTURE_CITY_BACKGROUND));
	deckCards->push_back(new FortifyCard(Mewtle::Game::generateId(), "First card", ResourceManager::TEXTURE_DRAW_PILE));
	deckCards->push_back(new FortifyCard(Mewtle::Game::generateId(), "First card", ResourceManager::TEXTURE_DISCARD_PILE));
	deckCards->push_back(new CardWall(Mewtle::Game::generateId()));
	deck = new Deck(deckCards);

	deck->init();
	deck->draw(10);
	//deck->discard((*deck->hand)[0]);
	//deck->draw(1);
}

void BattleState::tick(){
	Mewtle::Game::setLightPosition(Mewtle::Game::getCamera()->getCameraX(), Mewtle::Game::getCamera()->getCameraY(), Mewtle::Game::getCamera()->getCameraZ());
	if(buildPhase != nullptr) buildPhase->tick();
	//EventHandler::executeEvents();
}

void BattleState::render(){
	city->render();
	Building::renderAllPlaced();
	if(buildPhase != nullptr){
		buildPhase->render();
	}
	NPC::renderAll();
	deck->render();
	Mewtle::Button::renderAll();
	//Mewtle::Game::drawAllEntities();
	//Mewtle::Game::drawAllGuiElements();
}

void BattleState::keyboardInput(){
	float temp = 0.01f;
	if(buildPhase != nullptr) buildPhase->keyboardInput();
	if(Mewtle::Game::keyPressed(GLFW_KEY_UP)){
		glm::mat4 rotationMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::rotate(rotationMatrix, -(Mewtle::Game::getCamera()->getRotZ() - (float) M_PI / 4), glm::vec3(0, 0, 1));
		glm::vec4 tempVector = glm::vec4(0, temp, 0, 1);
		tempVector = rotationMatrix * tempVector;		
		Mewtle::Game::translateCamera(tempVector.x, tempVector.y, tempVector.z);
	}
	if(Mewtle::Game::keyPressed(GLFW_KEY_DOWN)){
		glm::mat4 rotationMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::rotate(rotationMatrix, -(Mewtle::Game::getCamera()->getRotZ() - (float)M_PI / 4), glm::vec3(0, 0, 1));
		glm::vec4 tempVector = glm::vec4(0, -temp, 0, 1);
		tempVector = rotationMatrix * tempVector;
		Mewtle::Game::translateCamera(tempVector.x, tempVector.y, tempVector.z);
	}
	if(Mewtle::Game::keyPressed(GLFW_KEY_LEFT)){
		glm::mat4 rotationMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::rotate(rotationMatrix, -(Mewtle::Game::getCamera()->getRotZ() - (float)M_PI / 4), glm::vec3(0, 0, 1));
		glm::vec4 tempVector = glm::vec4(-temp, 0, 0, 1);
		tempVector = rotationMatrix * tempVector;
		Mewtle::Game::translateCamera(tempVector.x, tempVector.y, tempVector.z);
	}
	if(Mewtle::Game::keyPressed(GLFW_KEY_RIGHT)){
		glm::mat4 rotationMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::rotate(rotationMatrix, -(Mewtle::Game::getCamera()->getRotZ() - (float)M_PI / 4), glm::vec3(0, 0, 1));
		glm::vec4 tempVector = glm::vec4(temp, 0, 0, 1);
		tempVector = rotationMatrix * tempVector;
		Mewtle::Game::translateCamera(tempVector.x, tempVector.y, tempVector.z);
	}
	if(Mewtle::Game::keyPressed(GLFW_KEY_E)){
		float temp4 = Mewtle::Game::getCamera()->getCameraX() + 1 * Mewtle::Utils::getScreenRatio();
		float temp3 = Mewtle::Game::getCamera()->getCameraY() + 2;
		float temp2 = Mewtle::Game::getCamera()->getCameraZ() - 2;
		Mewtle::Game::translateCamera(/*-temp4*/ + Mewtle::Utils::getScreenRatio(),/* temp3*/ -2 + Mewtle::Utils::convertHeightToOpenGL(city->getMapHeight() / 2), /*-temp2*/ - 2);
		Mewtle::Game::rotateCamera((float) M_PI / 50, 0, 0, 1);
		Mewtle::Game::translateCamera(/*temp4*/ - Mewtle::Utils::getScreenRatio(), /*-temp3 */+2 - Mewtle::Utils::convertHeightToOpenGL(city->getMapHeight() / 2), /*temp2*/ + 2);
	}
	if(Mewtle::Game::keyPressed(GLFW_KEY_Q)){
		float temp4 = Mewtle::Game::getCamera()->getCameraX() + 1 * Mewtle::Utils::getScreenRatio();
		float temp3 = Mewtle::Game::getCamera()->getCameraY() + 2;
		float temp2 = Mewtle::Game::getCamera()->getCameraZ() - 2;
		Mewtle::Game::translateCamera(/*-temp4*/ + Mewtle::Utils::getScreenRatio(),/* temp3*/ - 2 + Mewtle::Utils::convertHeightToOpenGL(city->getMapHeight() / 2), /*-temp2 */- 2);
		Mewtle::Game::rotateCamera((float) -M_PI / 50, 0, 0, 1);
		Mewtle::Game::translateCamera(/*temp4*/ - Mewtle::Utils::getScreenRatio(), /*-temp3 */+ 2 - Mewtle::Utils::convertHeightToOpenGL(city->getMapHeight() / 2), /*temp2 */+ 2);
	}
	if(Mewtle::Game::keyPressed(GLFW_KEY_R)){
		glm::mat4 rotationMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::rotate(rotationMatrix, -(Mewtle::Game::getCamera()->getRotZ() - (float)M_PI / 4), glm::vec3(0, 0, 1));
		glm::vec4 tempVector = glm::vec4(0, temp / sqrt(2), -temp / sqrt(2), 1);
		tempVector = rotationMatrix * tempVector;
		Mewtle::Game::translateCamera(tempVector.x, tempVector.y, tempVector.z);
	}
	if(Mewtle::Game::keyPressed(GLFW_KEY_F)){
		glm::mat4 rotationMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::rotate(rotationMatrix, -(Mewtle::Game::getCamera()->getRotZ() - (float)M_PI / 4), glm::vec3(0, 0, 1));
		glm::vec4 tempVector = glm::vec4(0, -temp / sqrt(2), temp / sqrt(2), 1);
		tempVector = rotationMatrix * tempVector;
		Mewtle::Game::translateCamera(tempVector.x, tempVector.y, tempVector.z);
	}
}

void BattleState::mouseLeftPressed(double x, double y){
	if(buildPhase != nullptr){
		return;
	}
	bool flag = deck->mouseLeftPressed(x, y);
	if(flag) return;
	flag = Mewtle::Button::checkMouseLeftPressed(x, y);
	if(flag) return;
	else city->mouseLeftPressed(x, y);
}

void BattleState::mouseLeftReleased(double x, double y){
	if(buildPhase != nullptr){
		buildPhase->mouseLeftReleased(x, y);
		return;
	}
	bool flag = deck->mouseLeftReleased(x, y);
	if(flag) return;
	flag = Mewtle::Button::checkMouseLeftReleased(x, y);
	if(flag) return;
	else city->mouseLeftReleased(x, y);
}

void BattleState::mouseRightPressed(double x, double y){
	if(buildPhase != nullptr){
		buildPhase->mouseRightReleased(x, y);
		return;
	}
	bool flag = deck->mouseRightPressed(x, y);
	if(flag) return;
	flag = Mewtle::Button::checkMouseRightPressed(x, y);
	if(flag) return;
	else city->mouseRightPressed(x, y);
}

void BattleState::mouseRightReleased(double x, double y){
	if(buildPhase != nullptr){
		return;
	}
	bool flag = deck->mouseRightReleased(x, y);
	if(flag) return;
	flag = Mewtle::Button::checkMouseRightReleased(x, y);
	if(flag) return;
	else city->mouseRightReleased(x, y);
}

void BattleState::startBuildPhase(BuildingCard* card){
	buildPhase = new BuildPhase(card, city);
	buildPhase->start();
}

void BattleState::endBuildPhase(){
	buildPhase = nullptr;
}
