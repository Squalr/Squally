#include "CastleEnemyDeserializer.h"

CastleEnemyDeserializer::CastleEnemyDeserializer()
{
}

CastleEnemyDeserializer::~CastleEnemyDeserializer()
{
}

void CastleEnemyDeserializer::onDeserializationRequest(ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == PlatformerEntityDeserializer::KeyTypeEntity)
	{
		ValueMap properties = args->properties;
		std::string name = properties.at(SerializableObject::KeyName).asString();
		SerializableObject* newEntity = nullptr;

		if (name == Agnes::MapKeyEnemyAgnes)
		{
			newEntity = Agnes::deserialize(&properties);
		}
		else if (name == Executioner::MapKeyEnemyExecutioner)
		{
			newEntity = Executioner::deserialize(&properties);
		}
		else if (name == Guard::MapKeyEnemyGuard)
		{
			newEntity = Guard::deserialize(&properties);
		}
		else if (name == Reaper::MapKeyEnemyReaper)
		{
			newEntity = Reaper::deserialize(&properties);
		}
		else if (name == Jack::MapKeyEnemyJack)
		{
			newEntity = Jack::deserialize(&properties);
		}
		else if (name == Reaper::MapKeyEnemyReaper)
		{
			newEntity = Reaper::deserialize(&properties);
		}
		else if (name == Scarecrow::MapKeyEnemyScarecrow)
		{
			newEntity = Scarecrow::deserialize(&properties);
		}
		else if (name == Shade::MapKeyEnemyShade)
		{
			newEntity = Shade::deserialize(&properties);
		}
		else if (name == VampireLord::MapKeyEnemyVampireLord)
		{
			newEntity = VampireLord::deserialize(&properties);
		}
		else if (name == Vampiress::MapKeyEnemyVampiress)
		{
			newEntity = Vampiress::deserialize(&properties);
		}
		else if (name == Wraith::MapKeyEnemyWraith)
		{
			newEntity = Wraith::deserialize(&properties);
		}
		else if (name == Zombie::MapKeyEnemyZombie)
		{
			newEntity = Zombie::deserialize(&properties);
		}
		else if (name == ZombieErlic::MapKeyEnemyZombieErlic)
		{
			newEntity = ZombieErlic::deserialize(&properties);
		}

		if (newEntity != nullptr)
		{
			// Fire an event indicating successful deserialization
			args->callback(newEntity);
		}
	}
}
