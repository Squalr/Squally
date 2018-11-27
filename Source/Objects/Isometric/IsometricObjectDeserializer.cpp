#include "IsometricObjectDeserializer.h"

const std::string IsometricObjectDeserializer::KeyTypeIsometricObject = "iso_object";

void IsometricObjectDeserializer::initializeListeners()
{
	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::ObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void IsometricObjectDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == IsometricObjectDeserializer::KeyTypeIsometricObject)
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
