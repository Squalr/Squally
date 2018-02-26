#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/GameUtils.h"
#include "Objects/Hackables/HackableObject.h"
#include "Level/Backgrounds/JungleBackground.h"
#include "Level/Backgrounds/MountainBackground.h"
#include "Level/Environments/JungleEnvironment.h"
#include "Objects/Objects.h"
#include "Entities/Entities.h"

using namespace cocos2d;

class Parser
{
public:
	static Layer* initializeTileLayer(cocos_experimental::TMXTiledMap* map, std::string tileLayer);
	static Layer* initializeDecor(cocos_experimental::TMXTiledMap* map, std::string decorLayer);
	static Layer* initializeParallaxObjects(cocos_experimental::TMXTiledMap* map, std::string parallaxLayer);

	static Layer* initializeBackground(cocos_experimental::TMXTiledMap* map);
	static Layer* initializeEnvironment(cocos_experimental::TMXTiledMap* map);
	static Layer* initializeEntities(cocos_experimental::TMXTiledMap* map, std::function<void(HackableObject*)> registerHackableCallback);
	static Layer* initializeObjects(cocos_experimental::TMXTiledMap* map, std::function<void(HackableObject*)> registerHackableCallback);
	static Layer* initializeCollision(cocos_experimental::TMXTiledMap* map);

private:
	static Sprite* loadObject(ValueMap object);
};
