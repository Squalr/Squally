#include "ObeliskEnemyDeserializer.h"

ObeliskEnemyDeserializer* ObeliskEnemyDeserializer::instance = nullptr;

void ObeliskEnemyDeserializer::registerGlobalNode()
{
	if (ObeliskEnemyDeserializer::instance == nullptr)
	{
		ObeliskEnemyDeserializer::instance = new ObeliskEnemyDeserializer();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(ObeliskEnemyDeserializer::instance);
	}
}

ObeliskEnemyDeserializer::ObeliskEnemyDeserializer()
{
}

ObeliskEnemyDeserializer::~ObeliskEnemyDeserializer()
{
}

void ObeliskEnemyDeserializer::initializeListeners()
{
	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::ObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void ObeliskEnemyDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
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
		DeserializationEvents::TriggerObjectDeserialize(DeserializationEvents::ObjectDeserializationArgs(newEntity));
	}
}
