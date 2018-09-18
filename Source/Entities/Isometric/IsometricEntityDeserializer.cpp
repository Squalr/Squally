#include "IsometricEntityDeserializer.h"

const std::string IsometricEntityDeserializer::KeyTypeIsometricEntity = "iso_entity";

IsometricEntityDeserializer::IsometricEntityDeserializer()
{
}

IsometricEntityDeserializer::~IsometricEntityDeserializer()
{
}

void IsometricEntityDeserializer::onDeserializationRequest(ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == IsometricEntityDeserializer::KeyTypeIsometricEntity)
	{
		ValueMap properties = args->properties;
		std::string name = properties.at(SerializableObject::KeyName).asString();
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
		args->callback(newEntity);
	}
}
