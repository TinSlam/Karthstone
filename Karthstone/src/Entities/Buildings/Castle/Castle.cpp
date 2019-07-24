#include <MewtlePrecompiledHeaders.h>

#include "Castle.h"
#include "ResourceManager/ResourceManager.h"

Castle::Castle(int id, int tileWidth, int tileHeight, float depth)
	: Building(id, Mewtle::Model3D::getModel(ResourceManager::MODEL_CUBE), Mewtle::Texture::getTexture(ResourceManager::TEXTURE_CITY_GRID), tileWidth, tileHeight, depth){

}