#include "MechNpcDeserializer.h"

MechNpcDeserializer* MechNpcDeserializer::instance = nullptr;

void MechNpcDeserializer::registerGlobalNode()
{
	if (MechNpcDeserializer::instance == nullptr)
	{
		MechNpcDeserializer::instance = new MechNpcDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(MechNpcDeserializer::instance);
	}
}

MechNpcDeserializer::MechNpcDeserializer()
{
}

MechNpcDeserializer::~MechNpcDeserializer()
{
}

void MechNpcDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void MechNpcDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::MapKeyName).asString();
	SerializableObject* newEntity = nullptr;

	if (name == Atreus::MapKeyNpcAtreus)
	{
		newEntity = Atreus::deserialize(&properties);
	}
	else if (name == Illia::MapKeyNpcIllia)
	{
		newEntity = Illia::deserialize(&properties);
	}
	else if (name == Leon::MapKeyNpcLeon)
	{
		newEntity = Leon::deserialize(&properties);
	}
	else if (name == Mara::MapKeyNpcMara)
	{
		newEntity = Mara::deserialize(&properties);
	}
	else if (name == Marcel::MapKeyNpcMarcel)
	{
		newEntity = Marcel::deserialize(&properties);
	}
	else if (name == Piper::MapKeyNpcPiper)
	{
		newEntity = Piper::deserialize(&properties);
	}
	else if (name == QueenElise::MapKeyNpcQueenElise)
	{
		newEntity = QueenElise::deserialize(&properties);
	}
	else if (name == Radon::MapKeyNpcRadon)
	{
		newEntity = Radon::deserialize(&properties);
	}
	else if (name == Xenon::MapKeyNpcXenon)
	{
		newEntity = Xenon::deserialize(&properties);
	}
	else if (name == Ysara::MapKeyNpcYsara)
	{
		newEntity = Ysara::deserialize(&properties);
	}

	if (newEntity != nullptr)
	{
		// Fire an event indicating successful deserialization
		args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(newEntity));
	}
}
