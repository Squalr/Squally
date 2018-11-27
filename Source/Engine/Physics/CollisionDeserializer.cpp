#include "CollisionDeserializer.h"

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
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void CollisionDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
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

		// Fire an event indicating successful deserialization
		DeserializationEvents::TriggerObjectDeserialize(DeserializationEvents::ObjectDeserializationArgs(collisionObject));
	}
}
