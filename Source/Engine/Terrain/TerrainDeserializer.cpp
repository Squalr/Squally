#include "TerrainDeserializer.h"

TerrainDeserializer* TerrainDeserializer::instance = nullptr;

void TerrainDeserializer::registerGlobalNode()
{
	if (TerrainDeserializer::instance == nullptr)
	{
		TerrainDeserializer::instance = new TerrainDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(TerrainDeserializer::instance);
	}
}

TerrainDeserializer::TerrainDeserializer()
{
}

TerrainDeserializer::~TerrainDeserializer()
{
}

void TerrainDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void TerrainDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == TerrainObject::MapKeyTypeTerrain)
	{
		TerrainObject* terrainObject = TerrainObject::deserialize(&args->properties);

		// Fire an event indicating successful deserialization
		args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(terrainObject));
	}
}
