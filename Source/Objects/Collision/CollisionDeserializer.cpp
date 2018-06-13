#include "CollisionDeserializer.h"

CollisionDeserializer* CollisionDeserializer::instance = nullptr;

const std::string CollisionDeserializer::KeyCollisionTypeSolid = "solid";
const std::string CollisionDeserializer::KeyCollisionTypeWater = "water";
const std::string CollisionDeserializer::KeyCollisionTypeSolidNpc = "npc";
const std::string CollisionDeserializer::KeyCollisionTypeSolidNpcFlying = "npc-flying";

const std::string CollisionDeserializer::KeyCollisionPointsProperty = "points";

void CollisionDeserializer::registerGlobalNode()
{
	if (CollisionDeserializer::instance == nullptr)
	{
		CollisionDeserializer::instance = new CollisionDeserializer();

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

void CollisionDeserializer::initializeEventListeners()
{
	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::DeserializationRequestEvent,
		CC_CALLBACK_1(CollisionDeserializer::onDeserializationRequest, this)
	);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(deserializationRequestListener, this);
}

void CollisionDeserializer::onDeserializationRequest(EventCustom* eventCustom)
{
	DeserializationEvents::DeserializationRequestArgs* args = (DeserializationEvents::DeserializationRequestArgs*)(eventCustom->getUserData());

	if (args->typeName == CollisionObject::KeyTypeCollision)
	{
		ValueMap object = args->valueMap;
		ValueVector* polygonPoints = nullptr;

		if (!GameUtils::keyExists(object, SerializableObject::KeyWidth) ||
			!GameUtils::keyExists(object, SerializableObject::KeyHeight) ||
			!GameUtils::keyExists(object, SerializableObject::KeyXPosition) ||
			!GameUtils::keyExists(object, SerializableObject::KeyYPosition))
		{
			CCLOG("Missing properties on collision object");
			return;
		}

		std::string name = object.at(SerializableObject::KeyName).asString();
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

		if (name == CollisionDeserializer::KeyCollisionTypeSolid)
		{
			collisionGroup = CategoryGroup::G_Solid;
		}
		else if (name == CollisionDeserializer::KeyCollisionTypeWater)
		{
			collisionGroup = CategoryGroup::G_Water;
		}
		else if (name == CollisionDeserializer::KeyCollisionTypeSolidNpc)
		{
			collisionGroup = CategoryGroup::G_SolidNpc;
		}
		else if (name == CollisionDeserializer::KeyCollisionTypeSolidNpcFlying)
		{
			collisionGroup = CategoryGroup::G_SolidFlyingNpc;
		}
		else
		{
			CCLOG("Unknown collision name");
			return;
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

		// Fire an event indicating successful deserialization
		args->callback(collisionBox);
	}
}