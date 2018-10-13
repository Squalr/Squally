#include "CastleNpcDeserializer.h"

CastleNpcDeserializer::CastleNpcDeserializer()
{
}

CastleNpcDeserializer::~CastleNpcDeserializer()
{
}

void CastleNpcDeserializer::onDeserializationRequest(ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::KeyName).asString();
	SerializableObject* newEntity = nullptr;

	if (name == Erlic::MapKeyNpcErlic)
	{
		newEntity = Erlic::deserialize(&properties);
	}
	else if (name == Garin::MapKeyNpcGarin)
	{
		newEntity = Garin::deserialize(&properties);
	}
	else if (name == KingRedsong::MapKeyNpcKingRedsong)
	{
		newEntity = KingRedsong::deserialize(&properties);
	}
	else if (name == KingRedsongSlime::MapKeyNpcKingRedsongSlime)
	{
		newEntity = KingRedsongSlime::deserialize(&properties);
	}
	else if (name == Leroy::MapKeyNpcLeroy)
	{
		newEntity = Leroy::deserialize(&properties);
	}
	else if (name == Mabel::MapKeyNpcMabel)
	{
		newEntity = Mabel::deserialize(&properties);
	}
	else if (name == PrincessOpal::MapKeyNpcPrincessOpal)
	{
		newEntity = PrincessOpal::deserialize(&properties);
	}
	else if (name == Raven::MapKeyNpcRaven)
	{
		newEntity = Raven::deserialize(&properties);
	}
	else if (name == Rogas::MapKeyNpcRogas)
	{
		newEntity = Rogas::deserialize(&properties);
	}
	else if (name == Thurstan::MapKeyNpcThurstan)
	{
		newEntity = Thurstan::deserialize(&properties);
	}
	else if (name == Tyracius::MapKeyNpcTyracius)
	{
		newEntity = Tyracius::deserialize(&properties);
	}

	if (newEntity != nullptr)
	{
		// Fire an event indicating successful deserialization
		args->callback(newEntity);
	}
}
