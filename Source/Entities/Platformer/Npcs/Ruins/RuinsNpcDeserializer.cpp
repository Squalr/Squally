#include "RuinsNpcDeserializer.h"

#include "Engine/GlobalDirector.h"
#include "Entities/Platformer/Npcs/Ruins/RuinsNpcs.h"

using namespace cocos2d;

RuinsNpcDeserializer* RuinsNpcDeserializer::instance = nullptr;

void RuinsNpcDeserializer::registerGlobalNode()
{
	if (RuinsNpcDeserializer::instance == nullptr)
	{
		RuinsNpcDeserializer::instance = new RuinsNpcDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(RuinsNpcDeserializer::instance);
	}
}

RuinsNpcDeserializer::RuinsNpcDeserializer()
{
}

RuinsNpcDeserializer::~RuinsNpcDeserializer()
{
}

void RuinsNpcDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void RuinsNpcDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::MapKeyName).asString();
	SerializableObject* newEntity = nullptr;

	if (name == Ajax::MapKeyNpcAjax)
	{
		newEntity = Ajax::deserialize(&properties);
	}
	else if (name == Aphrodite::MapKeyNpcAphrodite)
	{
		newEntity = Aphrodite::deserialize(&properties);
	}
	else if (name == Ares::MapKeyNpcAres)
	{
		newEntity = Ares::deserialize(&properties);
	}
	else if (name == Athena::MapKeyNpcAthena)
	{
		newEntity = Athena::deserialize(&properties);
	}
	else if (name == Cleopatra::MapKeyNpcCleopatra)
	{
		newEntity = Cleopatra::deserialize(&properties);
	}
	else if (name == Geryon::MapKeyNpcGeryon)
	{
		newEntity = Geryon::deserialize(&properties);
	}
	else if (name == Griffin::MapKeyNpcGriffin)
	{
		newEntity = Griffin::deserialize(&properties);
	}
	else if (name == Hera::MapKeyNpcHera)
	{
		newEntity = Hera::deserialize(&properties);
	}
	else if (name == Horus::MapKeyNpcHorus)
	{
		newEntity = Horus::deserialize(&properties);
	}
	else if (name == Poseidon::MapKeyNpcPoseidon)
	{
		newEntity = Poseidon::deserialize(&properties);
	}
	else if (name == Zeus::MapKeyNpcZeus)
	{
		newEntity = Zeus::deserialize(&properties);
	}

	if (newEntity != nullptr)
	{
		// Fire an event indicating successful deserialization
		args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(newEntity));
	}
}
