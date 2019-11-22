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
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2(-16.0f, 0.0f),
		cocos2d::Vec2(16.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

CastleTerrain::~CastleTerrain()
{
}
