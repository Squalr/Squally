#include "TileCollision.h"

using namespace cocos2d;

void TileCollision::InitializeCollision(TMXTiledMap* map, TMXLayer* layer, TileCollision::CollisionGroupsEnum allowedTypes)
{
	for (int x = 0; x < layer->getLayerSize().width; x++)
	{
		for (int y = 0; y < layer->getLayerSize().height; y++)
		{
			Sprite* tile = layer->getTileAt(Vec2(x, y));

			if (tile == nullptr)
			{
				continue;
			}

			ValueMap properties = map->getPropertiesForGID(layer->getTileGIDAt(Vec2(x, y))).asValueMap();
			PhysicsBody* collisionBox = CreateTileCollision(tile->getContentSize(), properties.at("Tile").asString(), allowedTypes);

			if (collisionBox != nullptr)
			{
				tile->addComponent(collisionBox);
			}
		}
	}
}

PhysicsBody * TileCollision::CreateTileCollision(Size tileSize, std::string tileName, TileCollision::CollisionGroupsEnum allowedTypes)
{
	PhysicsBody* physicsBody = nullptr;
	Size collisionSize = Size(tileSize.width - 1, tileSize.height - 1);

	if (tileName == "grass-top-left")
	{
		if (allowedTypes & TileCollision::CollisionGroupsEnum::Solid)
		{
			physicsBody = PhysicsBody::createBox(collisionSize, PhysicsMaterial(0.0f, 0.0f, 0.0f));
			physicsBody->setDynamic(false);
			physicsBody->setContactTestBitmask(TileCollision::CollisionGroupsEnum::Solid);
		}
	}
	else if (tileName == "water" || tileName == "water-top")
	{
		if (allowedTypes & TileCollision::CollisionGroupsEnum::Water)
		{
			physicsBody = PhysicsBody::createBox(collisionSize, PhysicsMaterial(0.0f, 0.0f, 0.0f));
			physicsBody->setDynamic(false);
			physicsBody->setContactTestBitmask(TileCollision::CollisionGroupsEnum::Water);
		}
	}
	else
	{
		if (allowedTypes & TileCollision::CollisionGroupsEnum::Solid)
		{
			physicsBody = PhysicsBody::createBox(collisionSize, PhysicsMaterial(0.0f, 0.0f, 0.0f));
			physicsBody->setDynamic(false);
			physicsBody->setContactTestBitmask(TileCollision::CollisionGroupsEnum::Solid);
		}
	}

	return physicsBody;
}

