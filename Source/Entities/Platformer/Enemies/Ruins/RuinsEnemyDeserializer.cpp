#include "RuinsEnemyDeserializer.h"

RuinsEnemyDeserializer::RuinsEnemyDeserializer()
{
}

RuinsEnemyDeserializer::~RuinsEnemyDeserializer()
{
}

void RuinsEnemyDeserializer::onDeserializationRequest(ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::KeyName).asString();
	SerializableObject* newEntity = nullptr;

	if (name == AnubisPup::MapKeyEnemyAnubisPup)
	{
		newEntity = AnubisPup::deserialize(&properties);
	}
	else if (name == AnubisWarrior::MapKeyEnemyAnubisWarrior)
	{
		newEntity = AnubisWarrior::deserialize(&properties);
	}
	else if (name == Lioness::MapKeyEnemyLioness)
	{
		newEntity = Lioness::deserialize(&properties);
	}
	else if (name == LionMan::MapKeyEnemyLionMan)
	{
		newEntity = LionMan::deserialize(&properties);
	}
	else if (name == Medusa::MapKeyEnemyMedusa)
	{
		newEntity = Medusa::deserialize(&properties);
	}
	else if (name == Mermaid::MapKeyEnemyMermaid)
	{
		newEntity = Mermaid::deserialize(&properties);
	}
	else if (name == MummyPriest::MapKeyEnemyMummyPriest)
	{
		newEntity = MummyPriest::deserialize(&properties);
	}
	else if (name == MummyWarrior::MapKeyEnemyMummyWarrior)
	{
		newEntity = MummyWarrior::deserialize(&properties);
	}
	else if (name == Osiris::MapKeyEnemyOsiris)
	{
		newEntity = Osiris::deserialize(&properties);
	}
	else if (name == TigerMan::MapKeyEnemyTigerMan)
	{
		newEntity = TigerMan::deserialize(&properties);
	}
	else if (name == Tigress::MapKeyEnemyTigress)
	{
		newEntity = Tigress::deserialize(&properties);
	}

	if (newEntity != nullptr)
	{
		// Fire an event indicating successful deserialization
		args->callback(newEntity);
	}
}
