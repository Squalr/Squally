#include "ForestEnemyDeserializer.h"

ForestEnemyDeserializer::ForestEnemyDeserializer()
{
}

ForestEnemyDeserializer::~ForestEnemyDeserializer()
{
}

void ForestEnemyDeserializer::initializeListeners()
{
	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::ObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void ForestEnemyDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::KeyName).asString();
	SerializableObject* newEntity = nullptr;

	if (name == Centaur::MapKeyEnemyCentaur)
	{
		newEntity = Centaur::deserialize(&properties);
	}
	else if (name == Cyclops::MapKeyEnemyCyclops)
	{
		newEntity = Cyclops::deserialize(&properties);
	}
	else if (name == Ent::MapKeyEnemyEnt)
	{
		newEntity = Ent::deserialize(&properties);
	}
	else if (name == KingGrogg::MapKeyEnemyKingGrogg)
	{
		newEntity = KingGrogg::deserialize(&properties);
	}
	else if (name == Ogre::MapKeyEnemyOgre)
	{
		newEntity = Ogre::deserialize(&properties);
	}
	else if (name == OrcBomber::MapKeyEnemyOrcBomber)
	{
		newEntity = OrcBomber::deserialize(&properties);
	}
	else if (name == OrcGrunt::MapKeyEnemyOrcGrunt)
	{
		newEntity = OrcGrunt::deserialize(&properties);
	}
	else if (name == OrcSwordsman::MapKeyEnemyOrcSwordsman)
	{
		newEntity = OrcSwordsman::deserialize(&properties);
	}
	else if (name == OrcWarrior::MapKeyEnemyOrcWarrior)
	{
		newEntity = OrcWarrior::deserialize(&properties);
	}
	else if (name == Thug::MapKeyEnemyThug)
	{
		newEntity = Thug::deserialize(&properties);
	}
	else if (name == Troll::MapKeyEnemyTroll)
	{
		newEntity = Troll::deserialize(&properties);
	}

	if (newEntity != nullptr)
	{
		// Fire an event indicating successful deserialization
		args->callback(newEntity);
	}
}
