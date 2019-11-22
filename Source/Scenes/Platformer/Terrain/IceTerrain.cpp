#include "IceTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string IceTerrain::MapKeyTerrainType = "ice";

IceTerrain* IceTerrain::create(ValueMap& properties)
{
	IceTerrain* instance = new IceTerrain(properties);

	instance->autorelease();

	return instance;
}

IceTerrain::IceTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		IceTerrain::MapKeyTerrainType,
		TextureResources::IceTexture,
		TerrainResources::Ice_Ice,
		TerrainResources::Ice_IceTopLeft,
		TerrainResources::Ice_IceTopRight,
		TerrainResources::Ice_IceBottom,
		TerrainResources::Ice_IceBottomLeft,
		TerrainResources::Ice_IceBottomRight,
		TerrainResources::Ice_IceLeft,
		TerrainResources::Ice_IceRight,
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

IceTerrain::~IceTerrain()
{
}
