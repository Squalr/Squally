#include "PlatformerObjectDeserializer.h"

const std::string PlatformerObjectDeserializer::KeyTypeObject = "object";

void PlatformerObjectDeserializer::initializeListeners()
{
	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::ObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void PlatformerObjectDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == PlatformerObjectDeserializer::KeyTypeObject)
	{
		ValueMap properties = args->properties;
		std::string name = properties.at(SerializableObject::KeyName).asString();
		SerializableObject* newObject = nullptr;

		if (name == "warp-gate")
		{
			newObject = WarpGate::create(&properties);
		}
		else if (name == "warp-gate-exact-scan-1")
		{
			newObject = WarpGateExactScanTutorial::create(&properties);
		}
		else if (name == "plushie_monkey")
		{
			newObject = PlushieMonkey::create(&properties);
		}
		else if (name == "monitor")
		{
			newObject = Monitor::create(&properties);
		}
		else if (name == "wind")
		{
			newObject = Wind::create(&properties);
		}
		else
		{
			CCLOG("Missing properties on platformer object");
			return;
		}

		args->callback(newObject);
	}
}
