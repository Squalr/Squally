#include "CollisionParser.h"

SerializableLayer* CollisionParser::parse(TMXObjectGroup* objectGroup)
{
	ValueVector collisionObjects = objectGroup->getObjects();
	SerializableLayer* layer = SerializableLayer::create(objectGroup);

	for (int index = 0; index < size(collisionObjects); index++)
	{
		if (collisionObjects[index].getType() != cocos2d::Value::Type::MAP)
		{
			continue;
		}

		ValueMap object = collisionObjects[index].asValueMap();
		ValueVector* polygonPoints = nullptr;

		if (!GameUtils::keyExists(object, CollisionKeys::CollisionTypeProperty) ||
			!GameUtils::keyExists(object, GeneralKeys::Width) ||
			!GameUtils::keyExists(object, GeneralKeys::Height) ||
			!GameUtils::keyExists(object, GeneralKeys::XPosition) ||
			!GameUtils::keyExists(object, GeneralKeys::YPosition))
		{
			CCLOG("Missing properties on collision object");
			continue;
		}

		std::string type = object.at(CollisionKeys::CollisionTypeProperty).asString();
		bool isPolygon = false;
		float width = object.at(GeneralKeys::Width).asFloat();
		float height = object.at(GeneralKeys::Height).asFloat();
		float x = object.at(GeneralKeys::XPosition).asFloat() + width / 2.0f;
		float y = object.at(GeneralKeys::YPosition).asFloat() + height / 2.0f;

		if (GameUtils::keyExists(object, CollisionKeys::CollisionPointsProperty))
		{
			isPolygon = true;
			polygonPoints = &(object.at(CollisionKeys::CollisionPointsProperty).asValueVector());
		}

		CollisionObject* collisionBox = new CollisionObject();
		CategoryGroup collisionGroup = CategoryGroup::G_None;

		if (type == CollisionKeys::CollisionTypeSolid)
		{
			collisionGroup = CategoryGroup::G_Solid;
		}
		else if (type == CollisionKeys::CollisionTypeWater)
		{
			collisionGroup = CategoryGroup::G_Water;
		}
		else if (type == CollisionKeys::CollisionTypeSolidNpc)
		{
			collisionGroup = CategoryGroup::G_SolidNpc;
		}
		else if (type == CollisionKeys::CollisionTypeSolidNpcFlying)
		{
			collisionGroup = CategoryGroup::G_SolidFlyingNpc;
		}
		else
		{
			CCLOG("Unknown collision type");
			continue;
		}

		if (isPolygon)
		{
			Vec2* points = new Vec2[polygonPoints->size()];
			int index = 0;

			for (auto it = polygonPoints->begin(); it != polygonPoints->end(); ++it)
			{
				auto point = it->asValueMap();

				float deltaX = point.at(GeneralKeys::XPosition).asFloat();
				float deltaY = point.at(GeneralKeys::YPosition).asFloat();

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
