#include "CavernsTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string CavernsTerrain::MapKeyTerrainType = "caverns";

CavernsTerrain* CavernsTerrain::create(ValueMap& properties)
{
	CavernsTerrain* instance = new CavernsTerrain(properties);

	instance->autorelease();

	return instance;
}

CavernsTerrain::CavernsTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		CavernsTerrain::MapKeyTerrainType,
		TextureResources::CavernsTexture,
		TerrainResources::Caverns_Caverns,
		TerrainResources::Caverns_CavernsTopLeft,
		TerrainResources::Caverns_CavernsTopRight,
		TerrainResources::Caverns_CavernsBottom,
		TerrainResources::Caverns_CavernsBottomLeft,
		TerrainResources::Caverns_CavernsBottomRight,
		TerrainResources::Caverns_CavernsLeft,
		TerrainResources::Caverns_CavernsRight,
		// Top
		Vec2::ZERO,
		// Bottom
		Vec2::ZERO,
		// Left
		Vec2::ZERO,
		// Right
		Vec2::ZERO,
		// TopLeft
		Vec2::ZERO,
		// TopRight
		Vec2::ZERO,
		// BottomLeft
		Vec2::ZERO,
		// BottomRight
		Vec2::ZERO,
		Color4B(14, 5, 2, 255)))
{
}

CavernsTerrain::~CavernsTerrain()
{
}
