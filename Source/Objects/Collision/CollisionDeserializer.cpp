#include "CollisionDeserializer.h"

CollisionDeserializer* CollisionDeserializer::instance = nullptr;

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
		int i = 0;
	}
}