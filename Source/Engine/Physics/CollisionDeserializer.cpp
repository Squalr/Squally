#include "CollisionDeserializer.h"

CollisionDeserializer::CollisionDeserializer()
{
}

CollisionDeserializer::~CollisionDeserializer()
{
}

void CollisionDeserializer::onDeserializationRequest(ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == CollisionObject::KeyTypeCollision)
	{
		ValueMap* properties = new ValueMap(args->properties);
		ValueVector* polygonPoints = nullptr;
		CategoryName categoryName = properties->at(SerializableObject::KeyName).asString();
		bool isPolygon = false;
		float width = properties->at(SerializableObject::KeyWidth).asFloat();
		float height = properties->at(SerializableObject::KeyHeight).asFloat();
		float x = properties->at(SerializableObject::KeyXPosition).asFloat() + width / 2.0f;
		float y = properties->at(SerializableObject::KeyYPosition).asFloat() + height / 2.0f;

		if (GameUtils::keyExists(properties, SerializableObject::KeyPoints))
		{
			isPolygon = true;
			polygonPoints = &(properties->at(SerializableObject::KeyPoints).asValueVector());
		}

		PhysicsBody* physicsBody = nullptr;

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

			physicsBody = PhysicsBody::createPolygon(points, polygonPoints->size(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
		}
		else
		{
			physicsBody = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(0.0f, 0.0f, 0.0f));
		}

		CollisionObject* collisionObject = new CollisionObject(properties, physicsBody, categoryName, false, false);

		// Fire event, allowing for the game to map what this collision object collides with
		DeserializationEvents::requestCollisionMapping(DeserializationEvents::CollisionMapRequestArgs(categoryName, collisionObject));

		// Fire an event indicating successful deserialization
		args->callback(collisionObject);
	}
}
