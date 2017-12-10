#pragma once
#include "cocos2d.h"

using namespace cocos2d;

static class TileCollision
{
public:
	const static enum CollisionGroupsEnum
	{
		Solid = 1 << 1,
		PassThrough = 1 << 2,
		Water = 1 << 3,
		Lava = 1 << 4,
		Liquid = Water | Lava,
		Entity = Solid | PassThrough | Water | Lava,
		All = Solid | PassThrough | Water | Lava
	};

	static void InitializeCollision(TMXTiledMap* map, TMXLayer* layer, TileCollision::CollisionGroupsEnum allowedTypes);

private:
	static PhysicsBody * CreateTileCollision(Size tileSize, std::string tileName, TileCollision::CollisionGroupsEnum allowedTypes);
};
