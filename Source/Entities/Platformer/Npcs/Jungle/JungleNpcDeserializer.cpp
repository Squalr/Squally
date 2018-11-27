#include "JungleNpcDeserializer.h"

JungleNpcDeserializer* JungleNpcDeserializer::instance = nullptr;

void JungleNpcDeserializer::registerGlobalNode()
{
	if (JungleNpcDeserializer::instance == nullptr)
	{
		JungleNpcDeserializer::instance = new JungleNpcDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(JungleNpcDeserializer::instance);
	}
}

JungleNpcDeserializer::JungleNpcDeserializer()
{
}

JungleNpcDeserializer::~JungleNpcDeserializer()
{
}

void JungleNpcDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void JungleNpcDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::KeyName).asString();
	SerializableObject* newEntity = nullptr;

	if (name == Blackbeard::MapKeyNpcBlackbeard)
	{
		newEntity = Blackbeard::deserialize(&properties);
	}
	else if (name == Bodom::MapKeyNpcBodom)
	{
		newEntity = Bodom::deserialize(&properties);
	}
	else if (name == Drak::MapKeyNpcDrak)
	{
		newEntity = Drak::deserialize(&properties);
	}
	else if (name == Elriel::MapKeyNpcElriel)
	{
		newEntity = Elriel::deserialize(&properties);
	}
	else if (name == Gramps::MapKeyNpcGramps)
	{
		newEntity = Gramps::deserialize(&properties);
	}
	else if (name == Hades::MapKeyNpcHades)
	{
		newEntity = Hades::deserialize(&properties);
	}
	else if (name == Minos::MapKeyNpcMinos)
	{
		newEntity = Minos::deserialize(&properties);
	}
	else if (name == PrincessMatu::MapKeyNpcPrincessMatu)
	{
		newEntity = PrincessMatu::deserialize(&properties);
	}
	else if (name == Raka::MapKeyNpcRaka)
	{
		newEntity = Raka::deserialize(&properties);
	}
	else if (name == Thor::MapKeyNpcThor)
	{
		newEntity = Thor::deserialize(&properties);
	}

	if (newEntity != nullptr)
	{
		// Fire an event indicating successful deserialization
		args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(newEntity));
	}
}
