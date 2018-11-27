#include "VolcanoNpcDeserializer.h"

VolcanoNpcDeserializer* VolcanoNpcDeserializer::instance = nullptr;

void VolcanoNpcDeserializer::registerGlobalNode()
{
	if (VolcanoNpcDeserializer::instance == nullptr)
	{
		VolcanoNpcDeserializer::instance = new VolcanoNpcDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(VolcanoNpcDeserializer::instance);
	}
}

VolcanoNpcDeserializer::VolcanoNpcDeserializer()
{
}

VolcanoNpcDeserializer::~VolcanoNpcDeserializer()
{
}

void VolcanoNpcDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void VolcanoNpcDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::KeyName).asString();
	SerializableObject* newEntity = nullptr;

	if (name == Ash::MapKeyNpcAsh)
	{
		newEntity = Ash::deserialize(&properties);
	}
	else if (name == Brine::MapKeyNpcBrine)
	{
		newEntity = Brine::deserialize(&properties);
	}
	else if (name == Celeste::MapKeyNpcCeleste)
	{
		newEntity = Celeste::deserialize(&properties);
	}
	else if (name == Cindra::MapKeyNpcCindra)
	{
		newEntity = Cindra::deserialize(&properties);
	}
	else if (name == Igneus::MapKeyNpcIgneus)
	{
		newEntity = Igneus::deserialize(&properties);
	}
	else if (name == Lucifer::MapKeyNpcLucifer)
	{
		newEntity = Lucifer::deserialize(&properties);
	}
	else if (name == Magnus::MapKeyNpcMagnus)
	{
		newEntity = Magnus::deserialize(&properties);
	}
	else if (name == Pan::MapKeyNpcPan)
	{
		newEntity = Pan::deserialize(&properties);
	}
	else if (name == Ragnis::MapKeyNpcRagnis)
	{
		newEntity = Ragnis::deserialize(&properties);
	}
	else if (name == Scaldor::MapKeyNpcScaldor)
	{
		newEntity = Scaldor::deserialize(&properties);
	}
	else if (name == Zelina::MapKeyNpcZelina)
	{
		newEntity = Zelina::deserialize(&properties);
	}

	if (newEntity != nullptr)
	{
		// Fire an event indicating successful deserialization
		args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(newEntity));
	}
}
