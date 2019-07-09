#include "TerrainDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

TerrainDeserializer::TerrainDeserializer(TerrainObject::TerrainData terrainData) : super(TerrainObject::MapKeyTypeTerrain)
{
	this->terrainData = terrainData;
}

TerrainDeserializer::~TerrainDeserializer()
{
}

void TerrainDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
{
	if (GameUtils::getKeyOrDefault(args->properties, TerrainObject::MapKeyTypeTexture, Value("")).asString() == this->terrainData.textureMapKeyValue)
	{
		TerrainObject* terrainObject = TerrainObject::deserialize(args->properties, this->terrainData);

		// Fire an event indicating successful deserialization
		args->onDeserializeCallback(ObjectDeserializer::ObjectDeserializationArgs(terrainObject));
	}
}
