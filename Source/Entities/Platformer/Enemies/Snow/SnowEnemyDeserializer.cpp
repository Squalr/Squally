#include "SnowEnemyDeserializer.h"

SnowEnemyDeserializer::SnowEnemyDeserializer()
{
}

SnowEnemyDeserializer::~SnowEnemyDeserializer()
{
}

void SnowEnemyDeserializer::initializeListeners()
{
	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::ObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void SnowEnemyDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::KeyName).asString();
	SerializableObject* newEntity = nullptr;

	if (name == Cyrogen::MapKeyEnemyCyrogen)
	{
		newEntity = Cyrogen::deserialize(&properties);
	}
	else if (name == FrostFiend::MapKeyEnemyFrostFiend)
	{
		newEntity = FrostFiend::deserialize(&properties);
	}
	else if (name == GoblinElf::MapKeyEnemyGoblinElf)
	{
		newEntity = GoblinElf::deserialize(&properties);
	}
	else if (name == IceGolem::MapKeyEnemyIceGolem)
	{
		newEntity = IceGolem::deserialize(&properties);
	}
	else if (name == PenguinGrunt::MapKeyEnemyPenguinGrunt)
	{
		newEntity = PenguinGrunt::deserialize(&properties);
	}
	else if (name == PenguinWarrior::MapKeyEnemyPenguinWarrior)
	{
		newEntity = PenguinWarrior::deserialize(&properties);
	}
	else if (name == Santa::MapKeyEnemySanta)
	{
		newEntity = Santa::deserialize(&properties);
	}
	else if (name == SnowFiend::MapKeyEnemySnowFiend)
	{
		newEntity = SnowFiend::deserialize(&properties);
	}
	else if (name == ToySoldierGoblin::MapKeyEnemyToySoldierGoblin)
	{
		newEntity = ToySoldierGoblin::deserialize(&properties);
	}
	else if (name == WaterElemental::MapKeyEnemyWaterElemental)
	{
		newEntity = WaterElemental::deserialize(&properties);
	}
	else if (name == Yeti::MapKeyEnemyYeti)
	{
		newEntity = Yeti::deserialize(&properties);
	}
	else if (name == YetiWarrior::MapKeyEnemyYetiWarrior)
	{
		newEntity = YetiWarrior::deserialize(&properties);
	}

	if (newEntity != nullptr)
	{
		// Fire an event indicating successful deserialization
		args->callback(newEntity);
	}
}
