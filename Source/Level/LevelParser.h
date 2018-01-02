#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Level/Backgrounds/JungleBackground.h"
#include "Level/Backgrounds/MountainBackground.h"
#include "Level/Environments/JungleEnvironment.h"
#include "Utils/Utils.h"
#include "Entities/Player/Player.h"
#include "Entities/Enemies/Bat.h"
#include "Entities/Enemies/Poly.h"
#include "Entities/Enemies/Shroom.h"
#include "Entities/Enemies/Snail.h"
#include "Objects/WarpGate.h"
#include "Objects/WarpGateExactScanTutorial.h"

using namespace cocos2d;

class LevelParser
{
public:
	static Layer* initializeTileLayer(experimental::TMXTiledMap* map, std::string tileLayer);
	static Layer* initializeDecor(experimental::TMXTiledMap* map, std::string decorLayer);

	static Layer* initializeBackground(experimental::TMXTiledMap* map);
	static Layer* initializeEnvironment(experimental::TMXTiledMap* map);
	static Layer* initializeEntities(experimental::TMXTiledMap* map);
	static Layer* initializeObjects(experimental::TMXTiledMap* map);
	static Layer* initializeCollision(experimental::TMXTiledMap* map);

private:
};
