#include "VolcanoEnemyDeserializer.h"

VolcanoEnemyDeserializer::VolcanoEnemyDeserializer()
{
}

VolcanoEnemyDeserializer::~VolcanoEnemyDeserializer()
{
}

void VolcanoEnemyDeserializer::initializeListeners()
{
	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::ObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void VolcanoEnemyDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::KeyName).asString();
	SerializableObject* newEntity = nullptr;

	if (name == Asmodeus::MapKeyEnemyAsmodeus)
	{
		newEntity = Asmodeus::deserialize(&properties);
	}
	else if (name == CritterDemon::MapKeyEnemyCritterDemon)
	{
		newEntity = CritterDemon::deserialize(&properties);
	}
	else if (name == DemonDragon::MapKeyEnemyDemonDragon)
	{
		newEntity = DemonDragon::deserialize(&properties);
	}
	else if (name == DemonGhost::MapKeyEnemyDemonGhost)
	{
		newEntity = DemonGhost::deserialize(&properties);
	}
	else if (name == DemonGrunt::MapKeyEnemyDemonGrunt)
	{
		newEntity = DemonGrunt::deserialize(&properties);
	}
	else if (name == DemonRogue::MapKeyEnemyDemonRogue)
	{
		newEntity = DemonRogue::deserialize(&properties);
	}
	else if (name == DemonShaman::MapKeyEnemyDemonShaman)
	{
		newEntity = DemonShaman::deserialize(&properties);
	}
	else if (name == DemonSwordsman::MapKeyEnemyDemonSwordsman)
	{
		newEntity = DemonSwordsman::deserialize(&properties);
	}
	else if (name == DemonSwordsman::MapKeyEnemyDemonSwordsman)
	{
		newEntity = DemonSwordsman::deserialize(&properties);
	}
	else if (name == FireElemental::MapKeyEnemyFireElemental)
	{
		newEntity = FireElemental::deserialize(&properties);
	}
	else if (name == LavaGolem::MapKeyEnemyLavaGolem)
	{
		newEntity = LavaGolem::deserialize(&properties);
	}

	if (newEntity != nullptr)
	{
		// Fire an event indicating successful deserialization
		args->callback(newEntity);
	}
}
