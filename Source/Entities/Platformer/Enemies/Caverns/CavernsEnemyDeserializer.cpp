#include "CavernsEnemyDeserializer.h"

CavernsEnemyDeserializer::CavernsEnemyDeserializer()
{
}

CavernsEnemyDeserializer::~CavernsEnemyDeserializer()
{
}

void CavernsEnemyDeserializer::onDeserializationRequest(ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::KeyName).asString();
	SerializableObject* newEntity = nullptr;

	if (name == BlackWidow::MapKeyEnemyBlackWidow)
	{
		newEntity = BlackWidow::deserialize(&properties);
	}
	else if (name == EarthElemental::MapKeyEnemyEarthElemental)
	{
		newEntity = EarthElemental::deserialize(&properties);
	}
	else if (name == EarthGolem::MapKeyEnemyEarthGolem)
	{
		newEntity = EarthGolem::deserialize(&properties);
	}
	else if (name == ForestGolem::MapKeyEnemyForestGolem)
	{
		newEntity = ForestGolem::deserialize(&properties);
	}
	else if (name == Genie::MapKeyEnemyGenie)
	{
		newEntity = Genie::deserialize(&properties);
	}
	else if (name == Krampus::MapKeyEnemyKrampus)
	{
		newEntity = Krampus::deserialize(&properties);
	}
	else if (name == LightningGolem::MapKeyEnemyLightningGolem)
	{
		newEntity = LightningGolem::deserialize(&properties);
	}
	else if (name == Shaman::MapKeyEnemyShaman)
	{
		newEntity = Shaman::deserialize(&properties);
	}
	else if (name == SkeletalArcher::MapKeyEnemySkeletalArcher)
	{
		newEntity = SkeletalArcher::deserialize(&properties);
	}
	else if (name == SkeletalNecromancer::MapKeyEnemySkeletalNecromancer)
	{
		newEntity = SkeletalNecromancer::deserialize(&properties);
	}
	else if (name == SkeletalWarrior::MapKeyEnemySkeletalWarrior)
	{
		newEntity = SkeletalWarrior::deserialize(&properties);
	}

	if (newEntity != nullptr)
	{
		// Fire an event indicating successful deserialization
		args->callback(newEntity);
	}
}
