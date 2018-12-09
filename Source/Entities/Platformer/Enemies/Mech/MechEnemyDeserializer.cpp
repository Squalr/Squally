#include "MechEnemyDeserializer.h"

#include "Engine/GlobalDirector.h"
#include "Entities/Platformer/Enemies/Mech/MechEnemies.h"

using namespace cocos2d;

MechEnemyDeserializer* MechEnemyDeserializer::instance = nullptr;

void MechEnemyDeserializer::registerGlobalNode()
{
	if (MechEnemyDeserializer::instance == nullptr)
	{
		MechEnemyDeserializer::instance = new MechEnemyDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(MechEnemyDeserializer::instance);
	}
}

MechEnemyDeserializer::MechEnemyDeserializer()
{
}

MechEnemyDeserializer::~MechEnemyDeserializer()
{
}

void MechEnemyDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void MechEnemyDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::MapKeyName).asString();
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
		args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(newEntity));
	}
}
