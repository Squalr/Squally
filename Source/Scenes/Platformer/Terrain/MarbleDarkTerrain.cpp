#include "MarbleDarkTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string MarbleDarkTerrain::MapKeyTerrainType = "marble-dark";

MarbleDarkTerrain* MarbleDarkTerrain::create(ValueMap& properties)
{
	MarbleDarkTerrain* instance = new MarbleDarkTerrain(properties);

	instance->autorelease();

	return instance;
}

MarbleDarkTerrain::MarbleDarkTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		MarbleDarkTerrain::MapKeyTerrainType,
		TextureResources::MarbleDarkTexture,
		TerrainResources::MarbleDark_MarbleDark,
		TerrainResources::MarbleDark_MarbleDarkTopLeft,
		TerrainResources::MarbleDark_MarbleDarkTopRight,
		TerrainResources::MarbleDark_MarbleDarkBottom,
		TerrainResources::MarbleDark_MarbleDarkBottomLeft,
		TerrainResources::MarbleDark_MarbleDarkBottomRight,
		TerrainResources::MarbleDark_MarbleDarkLeft,
		TerrainResources::MarbleDark_MarbleDarkRight,
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

MarbleDarkTerrain::~MarbleDarkTerrain()
{
}
