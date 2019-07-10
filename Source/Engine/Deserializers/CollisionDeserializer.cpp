#include "CollisionDeserializer.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string CollisionDeserializer::MapKeyTypeCollision = "collision";

CollisionDeserializer* CollisionDeserializer::create()
{
	CollisionDeserializer* instance = new CollisionDeserializer();

	instance->autorelease();

	return instance;
}

CollisionDeserializer::CollisionDeserializer() : super(CollisionObject::MapKeyTypeCollision)
{
}

CollisionDeserializer::~CollisionDeserializer()
{
}

void CollisionDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = GameUtils::getKeyOrDefault(args->properties, GameObject::MapKeyName, Value("")).asString();

	float width = properties.at(GameObject::MapKeyWidth).asFloat();
	float height = properties.at(GameObject::MapKeyHeight).asFloat();
	float x = properties.at(GameObject::MapKeyXPosition).asFloat() + width / 2.0f;
	float y = properties.at(GameObject::MapKeyYPosition).asFloat() + height / 2.0f;
	PhysicsBody* physicsBody = nullptr;

	if (GameUtils::keyExists(properties, GameObject::MapKeyPoints))
	{
		ValueVector polygonPoints = (properties.at(GameObject::MapKeyPoints).asValueVector());

		Vec2* points = new Vec2[polygonPoints.size()];
		int index = 0;

		for (auto it = polygonPoints.begin(); it != polygonPoints.end(); ++it)
		{
			auto point = it->asValueMap();

			float deltaX = point.at(GameObject::MapKeyXPosition).asFloat();
			float deltaY = point.at(GameObject::MapKeyYPosition).asFloat();

			// Negate the Y since we're operating in a different coordinate system
			points[index++] = Vec2(deltaX, -deltaY);
		}

		physicsBody = PhysicsBody::createPolygon(points, polygonPoints.size(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	}
	else
	{
		physicsBody = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	}

	CollisionObject* collisionObject = new CollisionObject(properties, physicsBody, name, false, false);

	// Fire an event indicating successful deserialization
	args->onDeserializeCallback(ObjectDeserializer::ObjectDeserializationArgs(collisionObject));
}
