#include "IsometricObjectDeserializer.h"

const std::string IsometricObjectDeserializer::KeyTypeObject = "iso_object";

void IsometricObjectDeserializer::onDeserializationRequest(ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == IsometricObjectDeserializer::KeyTypeObject)
	{
		ValueMap properties = args->properties;
		std::string name = properties.at(SerializableObject::KeyName).asString();
		SerializableObject* newObject = nullptr;

		if (name == "hexus")
		{
			newObject = HexusArcade::create(&properties);
		}
		else
		{
			CCLOG("Missing properties on isometric object");
			return;
		}

		args->callback(newObject);
	}
}
