#include "JungleEnemyDeserializer.h"

JungleEnemyDeserializer::JungleEnemyDeserializer()
{
}

JungleEnemyDeserializer::~JungleEnemyDeserializer()
{
}

void JungleEnemyDeserializer::onDeserializationRequest(ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::KeyName).asString();
	SerializableObject* newEntity = nullptr;

	if (name == Barbarian::MapKeyEnemyBarbarian)
	{
		newEntity = Barbarian::deserialize(&properties);
	}
	else if (name == GoblinGruntBoar::MapKeyEnemyGoblinGruntBoar)
	{
		newEntity = GoblinGruntBoar::deserialize(&properties);
	}
	else if (name == GoblinShaman::MapKeyEnemyGoblinShaman)
	{
		newEntity = GoblinShaman::deserialize(&properties);
	}
	else if (name == GoblinWarriorPig::MapKeyEnemyGoblinWarriorPig)
	{
		newEntity = GoblinWarriorPig::deserialize(&properties);
	}
	else if (name == Gorilla::MapKeyEnemyGorilla)
	{
		newEntity = Gorilla::deserialize(&properties);
	}
	else if (name == Minotaur::MapKeyEnemyMinotaur)
	{
		newEntity = Minotaur::deserialize(&properties);
	}
	else if (name == ReanimatedPig::MapKeyEnemyReanimatedPig)
	{
		newEntity = ReanimatedPig::deserialize(&properties);
	}
	else if (name == Rhinoman::MapKeyEnemyRhinoman)
	{
		newEntity = Rhinoman::deserialize(&properties);
	}
	else if (name == SkeletalPirate::MapKeyEnemySkeletalPirate)
	{
		newEntity = SkeletalPirate::deserialize(&properties);
	}
	else if (name == TikiGolem::MapKeyEnemyTikiGolem)
	{
		newEntity = TikiGolem::deserialize(&properties);
	}
	else if (name == Viking::MapKeyEnemyViking)
	{
		newEntity = Viking::deserialize(&properties);
	}

	if (newEntity != nullptr)
	{
		// Fire an event indicating successful deserialization
		args->callback(newEntity);
	}
}
