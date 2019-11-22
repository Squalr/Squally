#include "CaveTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string CaveTerrain::MapKeyTerrainType = "cave";

CaveTerrain* CaveTerrain::create(ValueMap& properties)
{
	CaveTerrain* instance = new CaveTerrain(properties);

	instance->autorelease();

	return instance;
}

CaveTerrain::CaveTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		CaveTerrain::MapKeyTerrainType,
		TextureResources::CaveTexture,
		TerrainResources::Cave_Cave,
		TerrainResources::Cave_CaveTopLeft,
		TerrainResources::Cave_CaveTopRight,
		TerrainResources::Cave_CaveBottom,
		TerrainResources::Cave_CaveBottomLeft,
		TerrainResources::Cave_CaveBottomRight,
		TerrainResources::Cave_CaveLeft,
		TerrainResources::Cave_CaveRight,
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2(-16.0f, 0.0f),
		cocos2d::Vec2(16.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

CaveTerrain::~CaveTerrain()
{
}
