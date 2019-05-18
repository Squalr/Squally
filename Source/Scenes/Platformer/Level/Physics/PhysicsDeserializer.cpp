#include "PhysicsDeserializer.h"

#include "cocos/2d/CCTMXObjectGroup.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Scenes/Platformer/Level/Physics/PhysicsLayer.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

PhysicsDeserializer* PhysicsDeserializer::instance = nullptr;
const std::string PhysicsDeserializer::MapKeyPhysicsLayer = "physics";

void PhysicsDeserializer::registerGlobalNode()
{
	if (PhysicsDeserializer::instance == nullptr)
	{
		PhysicsDeserializer::instance = new PhysicsDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(PhysicsDeserializer::instance);
	}
}

void PhysicsDeserializer::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestLayerDeserializeEvent,
		[=](EventCustom* eventCustom)
		{
			DeserializationEvents::LayerDeserializationRequestArgs* args = static_cast<DeserializationEvents::LayerDeserializationRequestArgs*>(eventCustom->getUserData());
			
			if (args != nullptr)
			{
				this->onDeserializationRequest(args);
			}
		}
	);

	this->addGlobalEventListener(deserializationRequestListener);
}

void PhysicsDeserializer::onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args)
{
	std::string name = args->objectGroup->getGroupName();
	ValueMap properties = args->objectGroup->getProperties();

	if (!GameUtils::keyExists(properties, SerializableLayer::KeyType))
	{
		return;
	}

	std::string type = properties.at(SerializableLayer::KeyType).asString();

	if (type != PhysicsDeserializer::MapKeyPhysicsLayer)
	{
		return;
	}

	args->handled = true;

	args->onDeserializeCallback(DeserializationEvents::LayerDeserializationArgs(PhysicsLayer::create(properties, name), args->objectGroup->layerIndex));
}
