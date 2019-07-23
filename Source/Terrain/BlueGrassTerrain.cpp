#include "BlueGrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string BlueGrassTerrain::MapKeyTerrainTypeBlueGrass = "blue-grass";

BlueGrassTerrain* BlueGrassTerrain::create(ValueMap& initProperties)
{
	BlueGrassTerrain* instance = new BlueGrassTerrain(initProperties);

	instance->autorelease();

	return instance;
}

BlueGrassTerrain::BlueGrassTerrain(ValueMap& initProperties) : super(
	initProperties,
	TerrainObject::TerrainData(
		0.5f,
		BlueGrassTerrain::MapKeyTerrainTypeBlueGrass,
		TerrainResources::BlueGrass_BlueGrassTexture,
		TerrainResources::BlueGrass_BlueGrass,
		TerrainResources::BlueGrass_BlueGrassTopLeft,
		TerrainResources::BlueGrass_BlueGrassTopRight,
		TerrainResources::BlueGrass_BlueGrassBottom,
		TerrainResources::BlueGrass_BlueGrassBottomLeft,
		TerrainResources::BlueGrass_BlueGrassBottomRight,
		TerrainResources::BlueGrass_BlueGrassLeft,
		TerrainResources::BlueGrass_BlueGrassRight,
		cocos2d::Vec2(-16.0f, 0.0f),
		cocos2d::Vec2(16.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255),
		false))
{
}

BlueGrassTerrain::~BlueGrassTerrain()
{
}
