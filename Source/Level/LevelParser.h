#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/Utils.h"
#include "Level/Backgrounds/JungleBackground.h"
#include "Level/Backgrounds/MountainBackground.h"
#include "Level/Environments/JungleEnvironment.h"
#include "Objects/Objects.h"
#include "Entities/Entities.h"

using namespace cocos2d;

class LevelParser
{
public:
	static Layer* initializeTileLayer(experimental::TMXTiledMap* map, std::string tileLayer);
	static Layer* initializeDecor(experimental::TMXTiledMap* map, std::string decorLayer);
	static Layer* initializeParallaxObjects(experimental::TMXTiledMap* map, std::string parallaxLayer);

	static Layer* initializeBackground(experimental::TMXTiledMap* map);
	static Layer* initializeEnvironment(experimental::TMXTiledMap* map);
	static Layer* initializeEntities(experimental::TMXTiledMap* map);
	static Layer* initializeObjects(experimental::TMXTiledMap* map);
	static Layer* initializeCollision(experimental::TMXTiledMap* map);

private:
	static Sprite* loadObject(ValueMap object);
};
