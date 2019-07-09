#include "CavernsTerrainDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string CavernsTerrainDeserializer::MapKeyTerrainTypeCaverns = "caverns";

CavernsTerrainDeserializer* CavernsTerrainDeserializer::create()
{
	CavernsTerrainDeserializer* instance = new CavernsTerrainDeserializer();

	instance->autorelease();

	return instance;
}

CavernsTerrainDeserializer::CavernsTerrainDeserializer() : TerrainDeserializer(
	TerrainObject::TerrainData(
		0.5f,
		CavernsTerrainDeserializer::MapKeyTerrainTypeCaverns,
		TerrainResources::Caverns_CavernsTexture,
		TerrainResources::Caverns_Caverns,
		TerrainResources::Caverns_CavernsTopLeft,
		TerrainResources::Caverns_CavernsTopRight,
		TerrainResources::Caverns_CavernsBottom,
		TerrainResources::Caverns_CavernsBottomLeft,
		TerrainResources::Caverns_CavernsBottomRight,
		TerrainResources::Caverns_CavernsLeft,
		TerrainResources::Caverns_CavernsRight,
		Color4B(14, 5, 2, 255)))
{
}

CavernsTerrainDeserializer::~CavernsTerrainDeserializer()
{
}
