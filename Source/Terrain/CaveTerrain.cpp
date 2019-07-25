#include "CaveTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string CaveTerrain::MapKeyTerrainTypeCave = "cave";

CaveTerrain* CaveTerrain::create(ValueMap& initProperties)
{
	CaveTerrain* instance = new CaveTerrain(initProperties);

	instance->autorelease();

	return instance;
}

CaveTerrain::CaveTerrain(ValueMap& initProperties) : super(
	initProperties,
	TerrainObject::TerrainData(
		0.5f,
		CaveTerrain::MapKeyTerrainTypeCave,
		TerrainResources::Cave_CaveTexture,
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
