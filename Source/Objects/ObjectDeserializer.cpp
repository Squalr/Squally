#include "ObjectDeserializer.h"

const std::string ObjectDeserializer::KeyTypeObject = "object";

void ObjectDeserializer::onDeserializationRequest(DeserializationRequestArgs* args)
{
	if (args->typeName == ObjectDeserializer::KeyTypeObject)
	{
		ValueMap object = args->valueMap;
		std::string name = object.at(SerializableObject::KeyName).asString();
		float width = object.at(SerializableObject::KeyWidth).asFloat();
		float height = object.at(SerializableObject::KeyHeight).asFloat();
		Size size = Size(width, height);

		HackableObject* newObject = nullptr;

		if (name == "warp-gate")
		{
			newObject = WarpGate::create();
		}
		else if (name == "warp-gate-exact-scan-1")
		{
			newObject = WarpGateExactScanTutorial::create();
		}
		else if (name == "plushie_monkey")
		{
			newObject = PlushieMonkey::create();
		}
		else if (name == "monitor")
		{
			string dialog = object.at("dialog").asString();

			newObject = Monitor::create("Dialog\\" + dialog + ".json");
		}
		else if (name == "wind")
		{
			float speedX = 0.0f;
			float speedY = 0.0f;

			if (GameUtils::keyExists(object, "speed-x"))
			{
				speedX = object.at("speed-x").asFloat();
			}

			if (GameUtils::keyExists(object, "speed-y"))
			{
				speedY = object.at("speed-y").asFloat();
			}

			newObject = Wind::create(size, Vec2(speedX, speedY));
		}
		else
		{
			CCLOG("Missing properties on object");
			return;
		}

		newObject->setPosition(Vec2(
			object.at(SerializableObject::KeyXPosition).asFloat() + object.at(SerializableObject::KeyWidth).asFloat() / 2.0f,
			object.at(SerializableObject::KeyYPosition).asFloat() + object.at(SerializableObject::KeyHeight).asFloat() / 2.0f)
		);

		args->callback(newObject);
	}
}
