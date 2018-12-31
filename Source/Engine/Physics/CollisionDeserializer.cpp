#include "CollisionDeserializer.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

CollisionDeserializer* CollisionDeserializer::instance = nullptr;

void CollisionDeserializer::registerGlobalNode()
{
	if (CollisionDeserializer::instance == nullptr)
	{
		CollisionDeserializer::instance = new CollisionDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(CollisionDeserializer::instance);
	}
}

CollisionDeserializer::CollisionDeserializer()
{
}

CollisionDeserializer::~CollisionDeserializer()
{
}

void CollisionDeserializer::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void CollisionDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == CollisionObject::MapKeyTypeCollision)
	{
		ValueMap* properties = new ValueMap(args->properties);
		ValueVector* polygonPoints = nullptr;
		std::string deserializedCollisionName = properties->at(SerializableObject::MapKeyName).asString();
		bool isPolygon = false;
		float width = properties->at(SerializableObject::MapKeyWidth).asFloat();
		float height = properties->at(SerializableObject::MapKeyHeight).asFloat();
		float x = properties->at(SerializableObject::MapKeyXPosition).asFloat() + width / 2.0f;
		float y = properties->at(SerializableObject::MapKeyYPosition).asFloat() + height / 2.0f;

		if (GameUtils::keyExists(properties, SerializableObject::MapKeyPoints))
		{
			isPolygon = true;
			polygonPoints = &(properties->at(SerializableObject::MapKeyPoints).asValueVector());
		}

		PhysicsBody* physicsBody = nullptr;

		if (isPolygon)
		{
			Vec2* points = new Vec2[polygonPoints->size()];
			int index = 0;

			for (auto it = polygonPoints->begin(); it != polygonPoints->end(); ++it)
			{
				auto point = it->asValueMap();

				float deltaX = point.at(SerializableObject::MapKeyXPosition).asFloat();
				float deltaY = point.at(SerializableObject::MapKeyYPosition).asFloat();

				// Negate the Y since we're operating in a different coordinate system
				points[index++] = Vec2(deltaX, -deltaY);
			}

			physicsBody = PhysicsBody::createPolygon(points, polygonPoints->size(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
		}
		else
		{
			physicsBody = PhysicsBody::createBox(Size(width, height), PhysicsMaterial(0.0f, 0.0f, 0.0f));
		}

		CollisionObject* collisionObject = new CollisionObject(properties, physicsBody, deserializedCollisionName, false, false);

		// Fire an event indicating successful deserialization
		args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(collisionObject));
	}
}
