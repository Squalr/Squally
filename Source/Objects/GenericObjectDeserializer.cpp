#include "GenericObjectDeserializer.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Objects/GenericObjects.h"

using namespace cocos2d;

GenericObjectDeserializer* GenericObjectDeserializer::instance = nullptr;
const std::string GenericObjectDeserializer::KeyTypeObject = "object";

void GenericObjectDeserializer::registerGlobalNode()
{
	if (GenericObjectDeserializer::instance == nullptr)
	{
		GenericObjectDeserializer::instance = new GenericObjectDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(GenericObjectDeserializer::instance);
	}
}

void GenericObjectDeserializer::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* eventCustom)
		{
			DeserializationEvents::ObjectDeserializationRequestArgs* args = static_cast<DeserializationEvents::ObjectDeserializationRequestArgs*>(eventCustom->getUserData());

			if (args != nullptr)
			{
				this->onDeserializationRequest(args);
			}
		}
	);

	this->addGlobalEventListener(deserializationRequestListener);
}

void GenericObjectDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == GenericObjectDeserializer::KeyTypeObject)
	{
		ValueMap properties = args->properties;
		std::string name = properties.at(SerializableObject::MapKeyName).asString();
		SerializableObject* newObject = nullptr;

		if (name == CameraFocus::MapKeyCameraFocus)
		{
			newObject = CameraFocus::create(properties);
		}
		else if (name == CameraScrollTracker::MapKeyCameraScrollTracker)
		{
			newObject = CameraScrollTracker::create(properties);
		}
		else
		{
			CCLOG("Missing properties on platformer object");
			return;
		}
		
		args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(newObject));
	}
}
