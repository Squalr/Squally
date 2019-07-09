#include "TrailTerrainDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string TrailTerrainDeserializer::MapKeyTerrainTypeTrail = "trail";

TrailTerrainDeserializer* TrailTerrainDeserializer::create()
{
	TrailTerrainDeserializer* instance = new TrailTerrainDeserializer();

	instance->autorelease();

	return instance;
}

TrailTerrainDeserializer::TrailTerrainDeserializer() : TerrainDeserializer(
	TerrainObject::TerrainData(
		0.5f,
		TrailTerrainDeserializer::MapKeyTerrainTypeTrail,
		TerrainResources::Trail_TrailTexture,
		TerrainResources::Trail_Trail,
		TerrainResources::Trail_TrailTopLeft,
		TerrainResources::Trail_TrailTopRight,
		TerrainResources::Trail_TrailBottom,
		TerrainResources::Trail_TrailBottomLeft,
		TerrainResources::Trail_TrailBottomRight,
		TerrainResources::Trail_TrailLeft,
		TerrainResources::Trail_TrailRight,
		Color4B(11, 30, 39, 255)))
{
}

TrailTerrainDeserializer::~TrailTerrainDeserializer()
{
}
