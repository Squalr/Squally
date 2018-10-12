#include "ForestEnemyDeserializer.h"

ForestEnemyDeserializer::ForestEnemyDeserializer()
{
}

ForestEnemyDeserializer::~ForestEnemyDeserializer()
{
}

void ForestEnemyDeserializer::onDeserializationRequest(ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::KeyName).asString();
	SerializableObject* newEntity = nullptr;

	//////////////////
	// CASTLE
	//////////////////
	if (name == Agnes::Key)
	{
		newEntity = BossJack::deserialize(&properties);
	}

	if (newEntity != nullptr)
	{
		// Fire an event indicating successful deserialization
		args->callback(newEntity);
	}
}
