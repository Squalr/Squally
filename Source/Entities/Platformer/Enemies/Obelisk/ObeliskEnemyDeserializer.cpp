#include "ObeliskEnemyDeserializer.h"

ObeliskEnemyDeserializer::ObeliskEnemyDeserializer()
{
}

ObeliskEnemyDeserializer::~ObeliskEnemyDeserializer()
{
}

void ObeliskEnemyDeserializer::onDeserializationRequest(ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::KeyName).asString();
	SerializableObject* newEntity = nullptr;

	if (name == Abomination::MapKeyEnemyAbomination)
	{
		newEntity = Abomination::deserialize(&properties);
	}
	else if (name == Gargoyle::MapKeyEnemyGargoyle)
	{
		newEntity = Gargoyle::deserialize(&properties);
	}
	else if (name == KingZul::MapKeyEnemyKingZul)
	{
		newEntity = KingZul::deserialize(&properties);
	}
	else if (name == ReanimatedFighter::MapKeyEnemyReanimatedFighter)
	{
		newEntity = ReanimatedFighter::deserialize(&properties);
	}
	else if (name == SkeletalBaron::MapKeyEnemySkeletalBaron)
	{
		newEntity = SkeletalBaron::deserialize(&properties);
	}
	else if (name == SkeletalCleaver::MapKeyEnemySkeletalCleaver)
	{
		newEntity = SkeletalCleaver::deserialize(&properties);
	}
	else if (name == SkeletalKnight::MapKeyEnemySkeletalKnight)
	{
		newEntity = SkeletalKnight::deserialize(&properties);
	}
	else if (name == SkeletalPriestess::MapKeyEnemySkeletalPriestess)
	{
		newEntity = SkeletalPriestess::deserialize(&properties);
	}
	else if (name == Undead::MapKeyEnemyUndead)
	{
		newEntity = Undead::deserialize(&properties);
	}
	else if (name == VoidArcher::MapKeyEnemyVoidArcher)
	{
		newEntity = VoidArcher::deserialize(&properties);
	}
	else if (name == VoidDemon::MapKeyEnemyVoidDemon)
	{
		newEntity = VoidDemon::deserialize(&properties);
	}

	if (newEntity != nullptr)
	{
		// Fire an event indicating successful deserialization
		args->callback(newEntity);
	}
}
