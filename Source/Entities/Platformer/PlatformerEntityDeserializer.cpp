#include "PlatformerEntityDeserializer.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Maps/SerializableObject.h"

////////////////////////////////////
// BEGIN: THIS CODE IS GENERATED: //
////V////V////V////V////V////V////V/

#include "Entities/Platformer/Enemies/Abomination.h"
#include "Entities/Platformer/Helpers/Gecko.h"

////Y////Y////Y////Y////Y////Y////Y/
// END: THIS CODE IS GENERATED    //
////////////////////////////////////

const std::string PlatformerEntityDeserializer::KeyTypeEntity = "entity";

PlatformerEntityDeserializer* PlatformerEntityDeserializer::instance = nullptr;

void PlatformerEntityDeserializer::registerGlobalNode()
{
	if (PlatformerEntityDeserializer::instance == nullptr)
	{
		PlatformerEntityDeserializer::instance = new PlatformerEntityDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(PlatformerEntityDeserializer::instance);
	}
}

PlatformerEntityDeserializer::PlatformerEntityDeserializer()
{
}

PlatformerEntityDeserializer::~PlatformerEntityDeserializer()
{
}

void PlatformerEntityDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void PlatformerEntityDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == PlatformerEntityDeserializer::KeyTypeEntity)
	{
		ValueMap properties = args->properties;
		std::string name = properties.at(SerializableObject::MapKeyName).asString();
		SerializableObject* newEntity = nullptr;

		////////////////////////////////////
		// BEGIN: THIS CODE IS GENERATED: //
		////X////X////X////X////X////X////X/

		if (name == Abomination::MapKeyAbomination)
		{
			newEntity = Abomination::deserialize(&properties);
		}
		else if (name == Gecko::MapKeyGecko)
		{
			newEntity = Gecko::deserialize(&properties);
		}

		////O////O////O////O////O////O////O/
		// END: THIS CODE IS GENERATED    //
		////////////////////////////////////

		if (newEntity != nullptr)
		{
			// Fire an event indicating successful deserialization
			args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(newEntity));
		}
	}
}
