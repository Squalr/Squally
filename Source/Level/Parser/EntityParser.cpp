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

		if (!GameUtils::keyExists(entity, "type") ||
			!GameUtils::keyExists(entity, "width") ||
			!GameUtils::keyExists(entity, "height") ||
			!GameUtils::keyExists(entity, "x") ||
			!GameUtils::keyExists(entity, "y"))
		{
			CCLOG("Missing properties on entity");
			continue;
		}

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
		else if (type == "harpy")
		{
			newEntity = Harpy::create();
		}
		else if (type == "mermaid")
		{
			newEntity = Mermaid::create();
		}
		else if (type == "boss_evil_eye")
		{
			newEntity = BossEvilEye::create();
		}
		else if (type == "black_widow")
		{
			newEntity = BlackWidow::create();
		}
		else if (type == "boss_demon_king")
		{
			newEntity = BossDemonKing::create();
		}
		else
		{
			CCLOG("Missing type on entity");
			continue;
		}

		newEntity->setPosition(Vec2(entity.at("x").asFloat() + entity.at("width").asFloat() / 2, entity.at("y").asFloat() + entity.at("height").asFloat() / 2));
		layer->addChild(newEntity);
	}

	return layer;
}
