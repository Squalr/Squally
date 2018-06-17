#include "ObjectDeserializer.h"

const std::string ObjectDeserializer::KeyTypeObject = "object";

void ObjectDeserializer::onDeserializationRequest(ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == ObjectDeserializer::KeyTypeObject)
	{
		ValueMap properties = args->properties;
		std::string name = properties.at(SerializableObject::KeyName).asString();
		float width = properties.at(SerializableObject::KeyWidth).asFloat();
		float height = properties.at(SerializableObject::KeyHeight).asFloat();
		Size size = Size(width, height);

		HackableObject* newObject = nullptr;

		if (name == "warp-gate")
		{
			newObject = WarpGate::create(new ValueMap(properties));
		}
		else if (name == "warp-gate-exact-scan-1")
		{
			newObject = WarpGateExactScanTutorial::create(new ValueMap(properties));
		}
		else if (name == "plushie_monkey")
		{
			newObject = PlushieMonkey::create(new ValueMap(properties));
		}
		else if (name == "monitor")
		{
			string dialog = properties.at("dialog").asString();

			newObject = Monitor::create(new ValueMap(properties), "Dialog\\" + dialog + ".json");
		}
		else if (name == "wind")
		{
			float speedX = 0.0f;
			float speedY = 0.0f;

			if (GameUtils::keyExists(&properties, "speed-x"))
			{
				speedX = properties.at("speed-x").asFloat();
			}

			if (GameUtils::keyExists(&properties, "speed-y"))
			{
				speedY = properties.at("speed-y").asFloat();
			}

			newObject = Wind::create(&properties, size, Vec2(speedX, speedY));
		}
		else
		{
			CCLOG("Missing properties on object");
			return;
		}

		newObject->setPosition(Vec2(
			properties.at(SerializableObject::KeyXPosition).asFloat() + properties.at(SerializableObject::KeyWidth).asFloat() / 2.0f,
			properties.at(SerializableObject::KeyYPosition).asFloat() + properties.at(SerializableObject::KeyHeight).asFloat() / 2.0f)
		);

		args->callback(newObject);
	}
}
