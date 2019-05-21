#include "TerrainDeserializer.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

TerrainDeserializer* TerrainDeserializer::instance = nullptr;

TerrainDeserializer::TerrainDeserializer(TerrainObject::TerrainData terrainData)
{
	this->terrainData = terrainData;
}

TerrainDeserializer::~TerrainDeserializer()
{
}

void TerrainDeserializer::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* eventCustom)
		{
			DeserializationEvents::ObjectDeserializationRequestArgs* args = static_cast<DeserializationEvents::ObjectDeserializationRequestArgs*>(eventCustom->getUserData());

			if (args != nullptr)
			{
				this->onDeserializationRequest(args);
			}
		}
	);

	this->addGlobalEventListener(deserializationRequestListener);
}

void TerrainDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == TerrainObject::MapKeyTypeTerrain)
	{
		if (GameUtils::keyExists(args->properties, TerrainObject::MapKeyTypeTexture))
		{
			if (args->properties[TerrainObject::MapKeyTypeTexture].asString() == this->terrainData.textureMapKeyValue)
			{
				TerrainObject* terrainObject = TerrainObject::deserialize(args->properties, this->terrainData);

				// Fire an event indicating successful deserialization
				args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(terrainObject));
			}
		}
	}
}
