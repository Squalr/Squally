#pragma once
#include "cocos2d.h"

using namespace cocos2d;

static class TileCollision
{
public:
	static void InitializeCollision(TMXTiledMap* map, TMXLayer* layer);

private:
	static PhysicsBody * CreateTileCollision(Size tileSize, std::string tileName);
};
