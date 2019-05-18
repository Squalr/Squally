#include "TrailTerrainDeserializer.h"

#include "Engine/GlobalDirector.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string TrailTerrainDeserializer::MapKeyTerrainTypeTrail = "trail";
TrailTerrainDeserializer* TrailTerrainDeserializer::instance = nullptr;

void TrailTerrainDeserializer::registerGlobalNode()
{
	if (TrailTerrainDeserializer::instance == nullptr)
	{
		TrailTerrainDeserializer::instance = new TrailTerrainDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(TrailTerrainDeserializer::instance);
	}
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
