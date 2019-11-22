#include "MarbleGrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string MarbleGrassTerrain::MapKeyTerrainType = "marble-grass";

MarbleGrassTerrain* MarbleGrassTerrain::create(ValueMap& properties)
{
	MarbleGrassTerrain* instance = new MarbleGrassTerrain(properties);

	instance->autorelease();

	return instance;
}

MarbleGrassTerrain::MarbleGrassTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		MarbleGrassTerrain::MapKeyTerrainType,
		TextureResources::MarbleGrassTexture,
		TerrainResources::MarbleGrass_MarbleGrass,
		TerrainResources::MarbleGrass_MarbleGrassTopLeft,
		TerrainResources::MarbleGrass_MarbleGrassTopRight,
		TerrainResources::MarbleGrass_MarbleGrassBottom,
		TerrainResources::MarbleGrass_MarbleGrassBottomLeft,
		TerrainResources::MarbleGrass_MarbleGrassBottomRight,
		TerrainResources::MarbleGrass_MarbleGrassLeft,
		TerrainResources::MarbleGrass_MarbleGrassRight,
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2(-16.0f, 0.0f),
		cocos2d::Vec2(16.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

MarbleGrassTerrain::~MarbleGrassTerrain()
{
}
