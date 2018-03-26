#include "CollisionParser.h"

Layer* CollisionParser::parse(TMXObjectGroup* objectGroup)
{
	ValueVector collisionObjects = objectGroup->getObjects();
	Layer* layer = Layer::create();

	for (int index = 0; index < size(collisionObjects); index++)
	{
		if (collisionObjects[index].getType() != cocos2d::Value::Type::MAP)
		{
			continue;
		}

		ValueMap object = collisionObjects[index].asValueMap();
		ValueVector* polygonPoints = nullptr;

		std::string type = object.at("type").asString();
		bool isPolygon = false;
		float width = object.at("width").asFloat();
		float height = object.at("height").asFloat();
		float x = object.at("x").asFloat() + width / 2.0f;
		float y = object.at("y").asFloat() + height / 2.0f;

		if (GameUtils::keyExists(object, "points"))
		{
			isPolygon = true;
			polygonPoints = &(object.at("points").asValueVector());
		}

		CollisionObject* collisionBox = new CollisionObject();
		CategoryGroup collisionGroup = CategoryGroup::G_None;

		if (type == "solid")
		{
			collisionGroup = CategoryGroup::G_Solid;
		}
		else if (type == "water")
		{
			collisionGroup = CategoryGroup::G_Water;
		}
		else if (type == "npc")
		{
			collisionGroup = CategoryGroup::G_SolidNpc;
		}
		else if (type == "npc-flying")
		{
			collisionGroup = CategoryGroup::G_SolidFlyingNpc;
		}
		else
		{
			throw std::invalid_argument("Invalid type");
		}

		if (isPolygon)
		{
			Vec2* points = new Vec2[polygonPoints->size()];
			int index = 0;

			for (auto it = polygonPoints->begin(); it != polygonPoints->end(); ++it)
			{
				auto point = it->asValueMap();

				float deltaX = point.at("x").asFloat();
				float deltaY = point.at("y").asFloat();

				points[index++] = Vec2(x + deltaX, y - deltaY);
			}

			collisionBox->init(PhysicsBody::createPolygon(points, polygonPoints->size(), PhysicsMaterial(0.0f, 0.0f, 0.0f)), collisionGroup, false, false);
		}
		else
		{
			collisionBox->init(PhysicsBody::createBox(Size(width, height), PhysicsMaterial(0.0f, 0.0f, 0.0f)), collisionGroup, false, false);
			collisionBox->setPosition(x, y);
		}

		layer->addChild(collisionBox);
	}

	return layer;
}
