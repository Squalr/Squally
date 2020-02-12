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
	std::vector<Vec2> shape = std::vector<Vec2>();

	if (GameUtils::keyExists(properties, GameObject::MapKeyPoints))
	{
		ValueVector polygonPoints = (properties.at(GameObject::MapKeyPoints).asValueVector());

		int index = 0;

		for (auto it = polygonPoints.begin(); it != polygonPoints.end(); ++it)
		{
			auto point = it->asValueMap();

			float deltaX = GameUtils::getKeyOrDefault(point, GameObject::MapKeyXPosition, Value(0.0f)).asFloat();
			float deltaY = GameUtils::getKeyOrDefault(point, GameObject::MapKeyYPosition, Value(0.0f)).asFloat();

			// Negate the Y since we're operating in a different coordinate system
			shape.push_back(Vec2(deltaX, -deltaY));
		}
	}
	else
	{
		shape = CollisionObject::createBox(Size(width, height));
	}

	CollisionObject* collisionObject = CollisionObject::create(properties, shape, name, false, false);

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
