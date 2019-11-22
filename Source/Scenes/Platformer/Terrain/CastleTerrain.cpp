#include "CastleTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string CastleTerrain::MapKeyTerrainType = "castle";

CastleTerrain* CastleTerrain::create(ValueMap& properties)
{
	CastleTerrain* instance = new CastleTerrain(properties);

	instance->autorelease();

	return instance;
}

CastleTerrain::CastleTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		CastleTerrain::MapKeyTerrainType,
		TextureResources::CastleTexture,
		TerrainResources::Castle_Castle,
		TerrainResources::Castle_CastleTopLeft,
		TerrainResources::Castle_CastleTopRight,
		TerrainResources::Castle_CastleBottom,
		TerrainResources::Castle_CastleBottomLeft,
		TerrainResources::Castle_CastleBottomRight,
		TerrainResources::Castle_CastleLeft,
		TerrainResources::Castle_CastleRight,
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

CastleTerrain::~CastleTerrain()
{
}
