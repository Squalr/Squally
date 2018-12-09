#include "CastleNpcDeserializer.h"

#include "Engine/GlobalDirector.h"
#include "Entities/Platformer/Npcs/Castle/CastleNpcs.h"

using namespace cocos2d;

CastleNpcDeserializer* CastleNpcDeserializer::instance = nullptr;

void CastleNpcDeserializer::registerGlobalNode()
{
	if (CastleNpcDeserializer::instance == nullptr)
	{
		CastleNpcDeserializer::instance = new CastleNpcDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(CastleNpcDeserializer::instance);
	}
}

CastleNpcDeserializer::CastleNpcDeserializer()
{
}

CastleNpcDeserializer::~CastleNpcDeserializer()
{
}

void CastleNpcDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void CastleNpcDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::MapKeyName).asString();
	SerializableObject* newEntity = nullptr;

	if (name == Erlic::MapKeyNpcErlic)
	{
		newEntity = Erlic::deserialize(&properties);
	}
	else if (name == Garin::MapKeyNpcGarin)
	{
		newEntity = Garin::deserialize(&properties);
	}
	else if (name == KingRedsong::MapKeyNpcKingRedsong)
	{
		newEntity = KingRedsong::deserialize(&properties);
	}
	else if (name == KingRedsongSlime::MapKeyNpcKingRedsongSlime)
	{
		newEntity = KingRedsongSlime::deserialize(&properties);
	}
	else if (name == Leroy::MapKeyNpcLeroy)
	{
		newEntity = Leroy::deserialize(&properties);
	}
	else if (name == Mabel::MapKeyNpcMabel)
	{
		newEntity = Mabel::deserialize(&properties);
	}
	else if (name == PrincessOpal::MapKeyNpcPrincessOpal)
	{
		newEntity = PrincessOpal::deserialize(&properties);
	}
	else if (name == Raven::MapKeyNpcRaven)
	{
		newEntity = Raven::deserialize(&properties);
	}
	else if (name == Rogas::MapKeyNpcRogas)
	{
		newEntity = Rogas::deserialize(&properties);
	}
	else if (name == Thurstan::MapKeyNpcThurstan)
	{
		newEntity = Thurstan::deserialize(&properties);
	}
	else if (name == Tyracius::MapKeyNpcTyracius)
	{
		newEntity = Tyracius::deserialize(&properties);
	}

	if (newEntity != nullptr)
	{
		// Fire an event indicating successful deserialization
		args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(newEntity));
	}
}
