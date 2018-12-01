#include "JungleEnemyDeserializer.h"

JungleEnemyDeserializer* JungleEnemyDeserializer::instance = nullptr;

void JungleEnemyDeserializer::registerGlobalNode()
{
	if (JungleEnemyDeserializer::instance == nullptr)
	{
		JungleEnemyDeserializer::instance = new JungleEnemyDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(JungleEnemyDeserializer::instance);
	}
}

JungleEnemyDeserializer::JungleEnemyDeserializer()
{
}

JungleEnemyDeserializer::~JungleEnemyDeserializer()
{
}

void JungleEnemyDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void JungleEnemyDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::MapKeyName).asString();
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
		args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(newEntity));
	}
}
