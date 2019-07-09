#include "CaveTerrainDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string CaveTerrainDeserializer::MapKeyTerrainTypeCave = "cave";

CaveTerrainDeserializer* CaveTerrainDeserializer::create()
{
	CaveTerrainDeserializer* instance = new CaveTerrainDeserializer();

	instance->autorelease();

	return instance;
}

CaveTerrainDeserializer::CaveTerrainDeserializer() : TerrainDeserializer(
	TerrainObject::TerrainData(
		0.5f,
		CaveTerrainDeserializer::MapKeyTerrainTypeCave,
		TerrainResources::Cave_CaveTexture,
		TerrainResources::Cave_Cave,
		TerrainResources::Cave_CaveTopLeft,
		TerrainResources::Cave_CaveTopRight,
		TerrainResources::Cave_CaveBottom,
		TerrainResources::Cave_CaveBottomLeft,
		TerrainResources::Cave_CaveBottomRight,
		TerrainResources::Cave_CaveLeft,
		TerrainResources::Cave_CaveRight,
		Color4B(11, 30, 39, 255)))
{
}

CaveTerrainDeserializer::~CaveTerrainDeserializer()
{
}
