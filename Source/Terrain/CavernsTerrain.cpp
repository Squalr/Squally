#include "CavernsTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string CavernsTerrain::MapKeyTerrainTypeCaverns = "caverns";

CavernsTerrain* CavernsTerrain::create(ValueMap& initProperties)
{
	CavernsTerrain* instance = new CavernsTerrain(initProperties);

	instance->autorelease();

	return instance;
}

CavernsTerrain::CavernsTerrain(ValueMap& initProperties) : super(
	initProperties,
	TerrainObject::TerrainData(
		0.5f,
		CavernsTerrain::MapKeyTerrainTypeCaverns,
		TerrainResources::Caverns_CavernsTexture,
		TerrainResources::Caverns_Caverns,
		TerrainResources::Caverns_CavernsTopLeft,
		TerrainResources::Caverns_CavernsTopRight,
		TerrainResources::Caverns_CavernsBottom,
		TerrainResources::Caverns_CavernsBottomLeft,
		TerrainResources::Caverns_CavernsBottomRight,
		TerrainResources::Caverns_CavernsLeft,
		TerrainResources::Caverns_CavernsRight,
		cocos2d::Vec2(-16.0f, 0.0f),
		cocos2d::Vec2(16.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(14, 5, 2, 255)))
{
}

CavernsTerrain::~CavernsTerrain()
{
}
