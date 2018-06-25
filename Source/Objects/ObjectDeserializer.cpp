#include "ObjectDeserializer.h"

const std::string ObjectDeserializer::KeyTypeObject = "object";

void ObjectDeserializer::onDeserializationRequest(ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == ObjectDeserializer::KeyTypeObject)
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
			CCLOG("Missing properties on object");
			return;
		}

		args->callback(newObject);
	}
}
