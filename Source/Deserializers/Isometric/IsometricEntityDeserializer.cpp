#include "IsometricEntityDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Entities/Isometric/IsometricEntities.h"

using namespace cocos2d;

const std::string IsometricEntityDeserializer::KeyTypeIsometricEntity = "iso_entity";

IsometricEntityDeserializer* IsometricEntityDeserializer::create()
{
	IsometricEntityDeserializer* instance = new IsometricEntityDeserializer();

	instance->autorelease();

	return instance;
}

IsometricEntityDeserializer::IsometricEntityDeserializer() : super(IsometricEntityDeserializer::KeyTypeIsometricEntity)
{
}

IsometricEntityDeserializer::~IsometricEntityDeserializer()
{
}

void IsometricEntityDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(GameObject::MapKeyName).asString();
	GameObject* newEntity = nullptr;

	if (name == IsometricSqually::KeySquallyProperty)
	{
		newEntity = IsometricSqually::deserialize(properties);
	}
	else if (name == IsometricBall::KeyBallProperty)
	{
		newEntity = IsometricBall::deserialize(properties);
	}
	else if (name == Shiftman::KeyShiftmanProperty)
	{
		newEntity = Shiftman::deserialize(properties);
	}
	else
	{
		CCLOG("Missing type on entity");
		return;
	}

	// Fire an event indicating successful deserialization
	if (newEntity != nullptr)
	{
		args->onDeserializeCallback(ObjectDeserializer::ObjectDeserializationArgs(newEntity));
	}
}
