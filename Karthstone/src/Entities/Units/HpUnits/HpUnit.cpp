#include <MewtlePrecompiledHeaders.h>

#include "HpUnit.h"

HpUnit::HpUnit(int id, Mewtle::Model3D* model, Mewtle::Texture* texture, float x, float y, float z, float rotX, float rotY, float rotZ, float width, float height, float depth, int maxHp) :
	Entity(id, model, texture, x, y, z, rotX, rotY, rotZ, width, height, depth){
	this->maxHp = maxHp;
}

HpUnit::~HpUnit(){

}

void HpUnit::setMaxHp(int value){
	this->maxHp = value;
}

void HpUnit::setHp(int value){
	this->hp = value;
}

void HpUnit::damage(int value){
	hp -= value;
}

int HpUnit::getMaxHp(){
	return maxHp;
}

int HpUnit::getHp(){
	return hp;
}