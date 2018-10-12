#include "RuinsNpcDeserializer.h"

RuinsNpcDeserializer::RuinsNpcDeserializer()
{
}

RuinsNpcDeserializer::~RuinsNpcDeserializer()
{
}

void RuinsNpcDeserializer::onDeserializationRequest(ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::KeyName).asString();
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
	else if (name == Manticore::MapKeyNpcManticore)
	{
		newEntity = Manticore::deserialize(&properties);
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
		args->callback(newEntity);
	}
}
