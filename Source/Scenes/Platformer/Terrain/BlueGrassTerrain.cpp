#include "BlueGrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string BlueGrassTerrain::MapKeyTerrainType = "blue-grass";

BlueGrassTerrain* BlueGrassTerrain::create(ValueMap& properties)
{
	BlueGrassTerrain* instance = new BlueGrassTerrain(properties);

	instance->autorelease();

	return instance;
}

BlueGrassTerrain::BlueGrassTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		BlueGrassTerrain::MapKeyTerrainType,
		TextureResources::BlueGrassTexture,
		TerrainResources::BlueGrass_BlueGrass,
		TerrainResources::BlueGrass_BlueGrassTopLeft,
		TerrainResources::BlueGrass_BlueGrassTopRight,
		TerrainResources::BlueGrass_BlueGrassBottom,
		TerrainResources::BlueGrass_BlueGrassBottomLeft,
		TerrainResources::BlueGrass_BlueGrassBottomRight,
		TerrainResources::BlueGrass_BlueGrassLeft,
		TerrainResources::BlueGrass_BlueGrassRight,
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2(-16.0f, 0.0f),
		cocos2d::Vec2(16.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

BlueGrassTerrain::~BlueGrassTerrain()
{
}
