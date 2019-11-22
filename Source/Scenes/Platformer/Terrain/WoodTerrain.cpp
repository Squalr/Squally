#include "WoodTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string WoodTerrain::MapKeyTerrainType = "wood";

WoodTerrain* WoodTerrain::create(ValueMap& properties)
{
	WoodTerrain* instance = new WoodTerrain(properties);

	instance->autorelease();

	return instance;
}

WoodTerrain::WoodTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		WoodTerrain::MapKeyTerrainType,
		TextureResources::WoodTexture,
		TerrainResources::Wood_Wood,
		TerrainResources::Wood_WoodTopLeft,
		TerrainResources::Wood_WoodTopRight,
		TerrainResources::Wood_WoodBottom,
		TerrainResources::Wood_WoodBottomLeft,
		TerrainResources::Wood_WoodBottomRight,
		TerrainResources::Wood_WoodLeft,
		TerrainResources::Wood_WoodRight,
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
		Color4B(11, 30, 39, 255)))
{
}

WoodTerrain::~WoodTerrain()
{
}
