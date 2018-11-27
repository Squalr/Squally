#include "CavernsNpcDeserializer.h"

CavernsNpcDeserializer* CavernsNpcDeserializer::instance = nullptr;

void CavernsNpcDeserializer::registerGlobalNode()
{
	if (CavernsNpcDeserializer::instance == nullptr)
	{
		CavernsNpcDeserializer::instance = new CavernsNpcDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(CavernsNpcDeserializer::instance);
	}
}

CavernsNpcDeserializer::CavernsNpcDeserializer()
{
}

CavernsNpcDeserializer::~CavernsNpcDeserializer()
{
}

void CavernsNpcDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void CavernsNpcDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(SerializableObject::KeyName).asString();
	SerializableObject* newEntity = nullptr;

	if (name == Alder::MapKeyNpcAlder)
	{
		newEntity = Alder::deserialize(&properties);
	}
	else if (name == Brock::MapKeyNpcBrock)
	{
		newEntity = Brock::deserialize(&properties);
	}
	else if (name == Cypress::MapKeyNpcCypress)
	{
		newEntity = Cypress::deserialize(&properties);
	}
	else if (name == Finch::MapKeyNpcFinch)
	{
		newEntity = Finch::deserialize(&properties);
	}
	else if (name == Fraya::MapKeyNpcFraya)
	{
		newEntity = Fraya::deserialize(&properties);
	}
	else if (name == Jasper::MapKeyNpcJasper)
	{
		newEntity = Jasper::deserialize(&properties);
	}
	else if (name == Mildred::MapKeyNpcMildred)
	{
		newEntity = Mildred::deserialize(&properties);
	}
	else if (name == Olive::MapKeyNpcOlive)
	{
		newEntity = Olive::deserialize(&properties);
	}
	else if (name == PrincessDawn::MapKeyNpcPrincessDawn)
	{
		newEntity = PrincessDawn::deserialize(&properties);
	}
	else if (name == Sarude::MapKeyNpcSarude)
	{
		newEntity = Sarude::deserialize(&properties);
	}
	else if (name == Shen::MapKeyNpcShen)
	{
		newEntity = Shen::deserialize(&properties);
	}

	if (newEntity != nullptr)
	{
		// Fire an event indicating successful deserialization
		DeserializationEvents::TriggerObjectDeserialize(DeserializationEvents::ObjectDeserializationArgs(newEntity));
	}
}
