#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Background.h"
#include "Utils/Utils.h"
#include "Entities/Player/Player.h"
#include "Entities/Enemies/Bat.h"
#include "Entities/Enemies/Shroom.h"
#include "Entities/Enemies/Snail.h"

using namespace cocos2d;

class LevelParser
{
public:
	static Layer* initializeBackgroundTiles(experimental::TMXTiledMap* map);
	static Layer* initializeMidgroundTiles(experimental::TMXTiledMap* map);
	static Layer* initializeForegroundTiles(experimental::TMXTiledMap* map);
	static Layer* initializeEnvironment(experimental::TMXTiledMap* map);
	static Layer* initializeObjects(experimental::TMXTiledMap* map);
	static Layer* initializeCollision(experimental::TMXTiledMap* map);
};
