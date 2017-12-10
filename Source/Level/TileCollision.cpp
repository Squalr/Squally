#include "TileCollision.h"
#include "../Collision/CollisionGroups.h"

using namespace cocos2d;

void TileCollision::InitializeCollision(TMXTiledMap* map, TMXLayer* layer)
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
			tile->addComponent(CreateTileCollision(tile->getContentSize(), properties.at("Tile").asString()));
		}
	}
}

PhysicsBody * TileCollision::CreateTileCollision(Size tileSize, std::string tileName)
{
	PhysicsBody* physicsBody = nullptr;

	if (tileName == "grass-top-left")
	{
		physicsBody = PhysicsBody::createBox(tileSize, PhysicsMaterial(0.0f, 0.0f, 0.0f));
		physicsBody->setDynamic(false);
		physicsBody->setContactTestBitmask(CollisionGroups::CollisionGroupsEnum::Solid);
	}
	else if (tileName == "water" || tileName == "water-top")
	{
		physicsBody = PhysicsBody::createBox(tileSize, PhysicsMaterial(0.0f, 0.0f, 0.0f));
		physicsBody->setDynamic(false);
		physicsBody->setContactTestBitmask(CollisionGroups::CollisionGroupsEnum::Water);
	}
	else
	{
		physicsBody = PhysicsBody::createBox(tileSize, PhysicsMaterial(0.0f, 0.0f, 0.0f));
		physicsBody->setDynamic(false);
		physicsBody->setContactTestBitmask(CollisionGroups::CollisionGroupsEnum::Solid);
	}

	return physicsBody;
}

