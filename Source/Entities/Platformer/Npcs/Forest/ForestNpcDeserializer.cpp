#include "ForestNpcDeserializer.h"

ForestNpcDeserializer* ForestNpcDeserializer::instance = nullptr;

void ForestNpcDeserializer::registerGlobalNode()
{
	if (ForestNpcDeserializer::instance == nullptr)
	{
		ForestNpcDeserializer::instance = new ForestNpcDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(ForestNpcDeserializer::instance);
	}
}

ForestNpcDeserializer::ForestNpcDeserializer()
{
}

ForestNpcDeserializer::~ForestNpcDeserializer()
{
}

void ForestNpcDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void ForestNpcDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::KeyName).asString();
	SerializableObject* newEntity = nullptr;

	if (name == Appolo::MapKeyNpcAppolo)
	{
		newEntity = Appolo::deserialize(&properties);
	}
	else if (name == Chiron::MapKeyNpcChiron)
	{
		newEntity = Chiron::deserialize(&properties);
	}
	else if (name == Cooper::MapKeyNpcCooper)
	{
		newEntity = Cooper::deserialize(&properties);
	}
	else if (name == Dudly::MapKeyNpcDudly)
	{
		newEntity = Dudly::deserialize(&properties);
	}
	else if (name == Lycan::MapKeyNpcLycan)
	{
		newEntity = Lycan::deserialize(&properties);
	}
	else if (name == Polyphemus::MapKeyNpcPolyphemus)
	{
		newEntity = Polyphemus::deserialize(&properties);
	}
	else if (name == PrincessMittens::MapKeyNpcPrincessMittens)
	{
		newEntity = PrincessMittens::deserialize(&properties);
	}
	else if (name == Robin::MapKeyNpcRobin)
	{
		newEntity = Robin::deserialize(&properties);
	}
	else if (name == Rupert::MapKeyNpcRupert)
	{
		newEntity = Rupert::deserialize(&properties);
	}
	else if (name == Rusty::MapKeyNpcRusty)
	{
		newEntity = Rusty::deserialize(&properties);
	}
	else if (name == Toben::MapKeyNpcToben)
	{
		newEntity = Toben::deserialize(&properties);
	}

	if (newEntity != nullptr)
	{
		// Fire an event indicating successful deserialization
		args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(newEntity));
	}
}
