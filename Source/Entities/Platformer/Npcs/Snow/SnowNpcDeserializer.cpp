#include "SnowNpcDeserializer.h"

SnowNpcDeserializer* SnowNpcDeserializer::instance = nullptr;

void SnowNpcDeserializer::registerGlobalNode()
{
	if (SnowNpcDeserializer::instance == nullptr)
	{
		SnowNpcDeserializer::instance = new SnowNpcDeserializer();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(SnowNpcDeserializer::instance);
	}
}

SnowNpcDeserializer::SnowNpcDeserializer()
{
}

SnowNpcDeserializer::~SnowNpcDeserializer()
{
}

void SnowNpcDeserializer::initializeListeners()
{
	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::ObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void SnowNpcDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::KeyName).asString();
	SerializableObject* newEntity = nullptr;

	if (name == Aspen::MapKeyNpcAspen)
	{
		newEntity = Aspen::deserialize(&properties);
	}
	else if (name == Aster::MapKeyNpcAster)
	{
		newEntity = Aster::deserialize(&properties);
	}
	else if (name == Cookie::MapKeyNpcCookie)
	{
		newEntity = Cookie::deserialize(&properties);
	}
	else if (name == Irmik::MapKeyNpcIrmik)
	{
		newEntity = Irmik::deserialize(&properties);
	}
	else if (name == Jingles::MapKeyNpcJingles)
	{
		newEntity = Jingles::deserialize(&properties);
	}
	else if (name == Juniper::MapKeyNpcJuniper)
	{
		newEntity = Juniper::deserialize(&properties);
	}
	else if (name == Kringle::MapKeyNpcKringle)
	{
		newEntity = Kringle::deserialize(&properties);
	}
	else if (name == Nessie::MapKeyNpcNessie)
	{
		newEntity = Nessie::deserialize(&properties);
	}
	else if (name == PrincessPepper::MapKeyNpcPrincessPepper)
	{
		newEntity = PrincessPepper::deserialize(&properties);
	}
	else if (name == Theldar::MapKeyNpcTheldar)
	{
		newEntity = Theldar::deserialize(&properties);
	}
	else if (name == Tinsel::MapKeyNpcTinsel)
	{
		newEntity = Tinsel::deserialize(&properties);
	}

	if (newEntity != nullptr)
	{
		// Fire an event indicating successful deserialization
		DeserializationEvents::TriggerObjectDeserialize(DeserializationEvents::ObjectDeserializationArgs(newEntity));
	}
}
