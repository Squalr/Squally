#include "SquallyDeserializer.h"

SquallyDeserializer* SquallyDeserializer::instance = nullptr;

void SquallyDeserializer::registerGlobalNode()
{
	if (SquallyDeserializer::instance == nullptr)
	{
		SquallyDeserializer::instance = new SquallyDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(SquallyDeserializer::instance);
	}
}

SquallyDeserializer::SquallyDeserializer()
{
}

SquallyDeserializer::~SquallyDeserializer()
{
}

void SquallyDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void SquallyDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == PlatformerEntityDeserializer::KeyTypeEntity)
	{
		ValueMap properties = args->properties;
		std::string name = properties.at(SerializableObject::KeyName).asString();
		SerializableObject* newEntity = nullptr;

		if (name == Squally::MapKeySqually)
		{
			newEntity = Squally::deserialize(&properties);
		}

		if (newEntity != nullptr)
		{
			// Fire an event indicating successful deserialization
			args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(newEntity));
		}
	}
}
