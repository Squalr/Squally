#include "PlatformerObjectDeserializer.h"

PlatformerObjectDeserializer* PlatformerObjectDeserializer::instance = nullptr;
const std::string PlatformerObjectDeserializer::KeyTypeObject = "object";

void PlatformerObjectDeserializer::registerGlobalNode()
{
	if (PlatformerObjectDeserializer::instance == nullptr)
	{
		PlatformerObjectDeserializer::instance = new PlatformerObjectDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(PlatformerObjectDeserializer::instance);
	}
}

void PlatformerObjectDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
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

		// TODO: Move these constants into their classes
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

		DeserializationEvents::TriggerObjectDeserialize(DeserializationEvents::ObjectDeserializationArgs(newObject));
	}
}
