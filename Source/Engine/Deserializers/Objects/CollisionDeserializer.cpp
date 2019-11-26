#include "CollisionDeserializer.h"

#include "Engine/Deserializers/Properties/PropertyDeserializer.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string CollisionDeserializer::MapKeyTypeCollision = "collision";

CollisionDeserializer* CollisionDeserializer::create(std::vector<PropertyDeserializer*> propertyDeserializers)
{
	CollisionDeserializer* instance = new CollisionDeserializer(propertyDeserializers);

	instance->autorelease();

	return instance;
}

CollisionDeserializer::CollisionDeserializer(std::vector<PropertyDeserializer*> propertyDeserializers) : super(CollisionObject::MapKeyTypeCollision, propertyDeserializers)
{
}

CollisionDeserializer::~CollisionDeserializer()
{
}

void CollisionDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = GameUtils::getKeyOrDefault(args->properties, GameObject::MapKeyName, Value("")).asString();

	float width = GameUtils::getKeyOrDefault(args->properties, GameObject::MapKeyWidth, Value(1.0f)).asFloat();
	float height = GameUtils::getKeyOrDefault(args->properties, GameObject::MapKeyHeight, Value(1.0f)).asFloat();
	float x = GameUtils::getKeyOrDefault(args->properties, GameObject::MapKeyXPosition, Value(0.0f)).asFloat() + width / 2.0f;
	float y = GameUtils::getKeyOrDefault(args->properties, GameObject::MapKeyYPosition, Value(0.0f)).asFloat() + height / 2.0f;
	float friction = GameUtils::getKeyOrDefault(args->properties, CollisionObject::MapKeyFriction, Value(1.0f)).asFloat();
	PhysicsBody* physicsBody = nullptr;

	if (GameUtils::keyExists(properties, GameObject::MapKeyPoints))
	{
		ValueVector polygonPoints = (properties.at(GameObject::MapKeyPoints).asValueVector());

		Vec2* points = new Vec2[polygonPoints.size()];
		int index = 0;

		for (auto it = polygonPoints.begin(); it != polygonPoints.end(); ++it)
		{
			auto point = it->asValueMap();

			float deltaX = GameUtils::getKeyOrDefault(point, GameObject::MapKeyXPosition, Value(0.0f)).asFloat();
			float deltaY = GameUtils::getKeyOrDefault(point, GameObject::MapKeyYPosition, Value(0.0f)).asFloat();

			// Negate the Y since we're operating in a different coordinate system
			points[index++] = Vec2(deltaX, -deltaY);
		}

		physicsBody = PhysicsBody::createPolygon(points, polygonPoints.size(), PhysicsMaterial(0.0f, 0.0f, friction));
	}
	else
	{
		physicsBody = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(0.0f, 0.0f, friction));
	}

	CollisionObject* collisionObject = CollisionObject::create(properties, physicsBody, name, false, false);

	for (auto it = this->propertyDeserializers.begin(); it != this->propertyDeserializers.end(); it++)
	{
		std::string key = GameUtils::getKeyOrDefault(properties, (*it)->getPropertyDeserializerKey(), Value("")).asString();

		if (!key.empty())
		{
			(*it)->deserializeProperties(collisionObject, properties);
		}
	}

	// Fire an event indicating successful deserialization
	args->onDeserializeCallback(ObjectDeserializer::ObjectDeserializationArgs(collisionObject));
}
