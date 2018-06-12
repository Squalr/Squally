#include "CollisionDeserializer.h"

const std::string CollisionDeserializer::KeyCollisionTypeProperty = "type";
const std::string CollisionDeserializer::KeyCollisionTypeSolid = "solid";
const std::string CollisionDeserializer::KeyCollisionTypeWater = "water";
const std::string CollisionDeserializer::KeyCollisionTypeSolidNpc = "npc";
const std::string CollisionDeserializer::KeyCollisionTypeSolidNpcFlying = "npc-flying";

const std::string CollisionDeserializer::KeyCollisionPointsProperty = "points";

SerializableLayer* CollisionDeserializer::deserialize(TMXObjectGroup* objectGroup)
{
	ValueVector collisionObjects = objectGroup->getObjects();
	SerializableLayer* layer = SerializableLayer::deserialize(objectGroup);

	for (int index = 0; index < size(collisionObjects); index++)
	{
		if (collisionObjects[index].getType() != cocos2d::Value::Type::MAP)
		{
			continue;
		}

		ValueMap object = collisionObjects[index].asValueMap();
		ValueVector* polygonPoints = nullptr;

		if (!GameUtils::keyExists(object, CollisionDeserializer::KeyCollisionTypeProperty) ||
			!GameUtils::keyExists(object, SerializableObject::KeyWidth) ||
			!GameUtils::keyExists(object, SerializableObject::KeyHeight) ||
			!GameUtils::keyExists(object, SerializableObject::KeyXPosition) ||
			!GameUtils::keyExists(object, SerializableObject::KeyYPosition))
		{
			CCLOG("Missing properties on collision object");
			continue;
		}

		std::string type = object.at(CollisionDeserializer::KeyCollisionTypeProperty).asString();
		bool isPolygon = false;
		float width = object.at(SerializableObject::KeyWidth).asFloat();
		float height = object.at(SerializableObject::KeyHeight).asFloat();
		float x = object.at(SerializableObject::KeyXPosition).asFloat() + width / 2.0f;
		float y = object.at(SerializableObject::KeyYPosition).asFloat() + height / 2.0f;

		if (GameUtils::keyExists(object, CollisionDeserializer::KeyCollisionPointsProperty))
		{
			isPolygon = true;
			polygonPoints = &(object.at(CollisionDeserializer::KeyCollisionPointsProperty).asValueVector());
		}

		CollisionObject* collisionBox = new CollisionObject();
		CategoryGroup collisionGroup = CategoryGroup::G_None;

		if (type == CollisionDeserializer::KeyCollisionTypeSolid)
		{
			collisionGroup = CategoryGroup::G_Solid;
		}
		else if (type == CollisionDeserializer::KeyCollisionTypeWater)
		{
			collisionGroup = CategoryGroup::G_Water;
		}
		else if (type == CollisionDeserializer::KeyCollisionTypeSolidNpc)
		{
			collisionGroup = CategoryGroup::G_SolidNpc;
		}
		else if (type == CollisionDeserializer::KeyCollisionTypeSolidNpcFlying)
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

				float deltaX = point.at(SerializableObject::KeyXPosition).asFloat();
				float deltaY = point.at(SerializableObject::KeyYPosition).asFloat();

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
