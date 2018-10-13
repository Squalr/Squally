#include "JungleNpcDeserializer.h"

JungleNpcDeserializer::JungleNpcDeserializer()
{
}

JungleNpcDeserializer::~JungleNpcDeserializer()
{
}

void JungleNpcDeserializer::onDeserializationRequest(ObjectDeserializationRequestArgs* args)
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
		args->callback(newEntity);
	}
}
