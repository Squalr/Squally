#include "RuinsEnemyDeserializer.h"

RuinsEnemyDeserializer* RuinsEnemyDeserializer::instance = nullptr;

void RuinsEnemyDeserializer::registerGlobalNode()
{
	if (RuinsEnemyDeserializer::instance == nullptr)
	{
		RuinsEnemyDeserializer::instance = new RuinsEnemyDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(RuinsEnemyDeserializer::instance);
	}
}

RuinsEnemyDeserializer::RuinsEnemyDeserializer()
{
}

RuinsEnemyDeserializer::~RuinsEnemyDeserializer()
{
}

void RuinsEnemyDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void RuinsEnemyDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
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
		DeserializationEvents::TriggerObjectDeserialize(DeserializationEvents::ObjectDeserializationArgs(newEntity));
	}
}
