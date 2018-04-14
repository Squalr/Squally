#include "EntityParser.h"

Layer* EntityParser::parse(TMXObjectGroup* objectGroup)
{
	Layer* layer = Layer::create();
	ValueVector entities = objectGroup->getObjects();

	// Create entities
	for (int index = 0; index < size(entities); index++)
	{
		if (entities[index].getType() != cocos2d::Value::Type::MAP)
		{
			continue;
		}

		ValueMap entity = entities[index].asValueMap();
		string type = entity.at("type").asString();

		HackableObject* newEntity = nullptr;

		if (type == "spawn")
		{
			newEntity = Player::create();
		}
		else if (type == "knight")
		{
			newEntity = Knight::create();
		}
		else if (type == "skeleton")
		{
			newEntity = Skeleton::create();
		}
		else if (type == "harpy")
		{
			newEntity = Harpy::create();
		}
		else if (type == "boss_demon_king")
		{
			newEntity = BossDemon::create();
		}
		else
		{
			continue;
		}

		newEntity->setPosition(Vec2(entity.at("x").asFloat() + entity.at("width").asFloat() / 2, entity.at("y").asFloat() + entity.at("height").asFloat() / 2));
		layer->addChild(newEntity);
	}

	return layer;
}
