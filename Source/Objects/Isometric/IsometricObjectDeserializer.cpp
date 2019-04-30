#include "IsometricObjectDeserializer.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Isometric/IsometricObjects.h"

using namespace cocos2d;

IsometricObjectDeserializer* IsometricObjectDeserializer::instance = nullptr;
const std::string IsometricObjectDeserializer::KeyTypeIsometricObject = "iso_object";

void IsometricObjectDeserializer::registerGlobalNode()
{
	if (IsometricObjectDeserializer::instance == nullptr)
	{
		IsometricObjectDeserializer::instance = new IsometricObjectDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(IsometricObjectDeserializer::instance);
	}
}

void IsometricObjectDeserializer::initializeListeners()
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

void IsometricObjectDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == IsometricObjectDeserializer::KeyTypeIsometricObject)
	{
		ValueMap properties = args->properties;
		std::string name = properties.at(SerializableObject::MapKeyName).asString();
		SerializableObject* newObject = nullptr;

		if (name == HexusArcade::MapKeyHexusArcade)
		{
			newObject = HexusArcade::create(properties);
		}
		else if (name == MemoryGrid::MapKeyMemoryGrid)
		{
			newObject = MemoryGrid::create(properties);
		}
		else if (name == EaxCrystal::MapKeyEaxCrystal)
		{
			newObject = EaxCrystal::create(properties);
		}
		else if (name == EaxJmp::MapKeyEaxJmp)
		{
			newObject = EaxJmp::create(properties);
		}
		else if (name == EaxPtrJmp::MapKeyEaxPtrJmp)
		{
			newObject = EaxPtrJmp::create(properties);
		}
		else
		{
			CCLOG("Missing properties on isometric object");
			return;
		}

		args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(newObject));
	}
}
