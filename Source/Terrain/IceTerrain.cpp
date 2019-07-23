#include "IceTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string IceTerrain::MapKeyTerrainTypeIce = "ice";

IceTerrain* IceTerrain::create(ValueMap& initProperties)
{
	IceTerrain* instance = new IceTerrain(initProperties);

	instance->autorelease();

	return instance;
}

IceTerrain::IceTerrain(ValueMap& initProperties) : super(
	initProperties,
	TerrainObject::TerrainData(
		0.5f,
		IceTerrain::MapKeyTerrainTypeIce,
		TerrainResources::Ice_IceTexture,
		TerrainResources::Ice_Ice,
		TerrainResources::Ice_IceTopLeft,
		TerrainResources::Ice_IceTopRight,
		TerrainResources::Ice_IceBottom,
		TerrainResources::Ice_IceBottomLeft,
		TerrainResources::Ice_IceBottomRight,
		TerrainResources::Ice_IceLeft,
		TerrainResources::Ice_IceRight,
		cocos2d::Vec2(-16.0f, 0.0f),
		cocos2d::Vec2(16.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255),
		false))
{
}

IceTerrain::~IceTerrain()
{
}
