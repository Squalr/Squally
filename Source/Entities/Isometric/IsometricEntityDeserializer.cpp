#include "IsometricEntityDeserializer.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Entities/Isometric/IsometricEntities.h"

using namespace cocos2d;

IsometricEntityDeserializer* IsometricEntityDeserializer::instance = nullptr;
const std::string IsometricEntityDeserializer::KeyTypeIsometricEntity = "iso_entity";

void IsometricEntityDeserializer::registerGlobalNode()
{
	if (IsometricEntityDeserializer::instance == nullptr)
	{
		IsometricEntityDeserializer::instance = new IsometricEntityDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(IsometricEntityDeserializer::instance);
	}
}

IsometricEntityDeserializer::IsometricEntityDeserializer()
{
}

IsometricEntityDeserializer::~IsometricEntityDeserializer()
{
}

void IsometricEntityDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void IsometricEntityDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == IsometricEntityDeserializer::KeyTypeIsometricEntity)
	{
		ValueMap properties = args->properties;
		std::string name = properties.at(SerializableObject::MapKeyName).asString();
		SerializableObject* newEntity = nullptr;

		if (name == IsometricSqually::KeySquallyProperty)
		{
			newEntity = IsometricSqually::deserialize(&properties);
		}
		else if (name == Shiftman::KeyShiftmanProperty)
		{
			newEntity = Shiftman::deserialize(&properties);
		}
		else
		{
			CCLOG("Missing type on entity");
			return;
		}

		// Fire an event indicating successful deserialization
		args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(newEntity));
	}
}
