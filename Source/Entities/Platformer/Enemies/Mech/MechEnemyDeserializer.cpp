#include "MechEnemyDeserializer.h"

MechEnemyDeserializer::MechEnemyDeserializer()
{
}

MechEnemyDeserializer::~MechEnemyDeserializer()
{
}

void MechEnemyDeserializer::onDeserializationRequest(ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::KeyName).asString();
	SerializableObject* newEntity = nullptr;

	if (name == EvilEye::MapKeyEnemyEvilEye)
	{
		newEntity = EvilEye::deserialize(&properties);
	}
	else if (name == Exterminator::MapKeyEnemyExterminator)
	{
		newEntity = Exterminator::deserialize(&properties);
	}
	else if (name == MechBoxDrone::MapKeyEnemyMechBoxDrone)
	{
		newEntity = MechBoxDrone::deserialize(&properties);
	}
	else if (name == MechDog::MapKeyEnemyMechDog)
	{
		newEntity = MechDog::deserialize(&properties);
	}
	else if (name == MechGolem::MapKeyEnemyMechGolem)
	{
		newEntity = MechGolem::deserialize(&properties);
	}
	else if (name == MechGuard::MapKeyEnemyMechGuard)
	{
		newEntity = MechGuard::deserialize(&properties);
	}
	else if (name == MiteBot::MapKeyEnemyMiteBot)
	{
		newEntity = MiteBot::deserialize(&properties);
	}
	else if (name == VikingBot::MapKeyEnemyVikingBot)
	{
		newEntity = VikingBot::deserialize(&properties);
	}
	else if (name == VikingBotSmall::MapKeyEnemyVikingBotSmall)
	{
		newEntity = VikingBotSmall::deserialize(&properties);
	}

	if (newEntity != nullptr)
	{
		// Fire an event indicating successful deserialization
		args->callback(newEntity);
	}
}
