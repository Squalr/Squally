#include "IceTerrainDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string IceTerrainDeserializer::MapKeyTerrainTypeIce = "ice";

IceTerrainDeserializer* IceTerrainDeserializer::create()
{
	IceTerrainDeserializer* instance = new IceTerrainDeserializer();

	instance->autorelease();

	return instance;
}

IceTerrainDeserializer::IceTerrainDeserializer() : TerrainDeserializer(
	TerrainObject::TerrainData(
		0.5f,
		IceTerrainDeserializer::MapKeyTerrainTypeIce,
		TerrainResources::Ice_IceTexture,
		TerrainResources::Ice_Ice,
		TerrainResources::Ice_IceTopLeft,
		TerrainResources::Ice_IceTopRight,
		TerrainResources::Ice_IceBottom,
		TerrainResources::Ice_IceBottomLeft,
		TerrainResources::Ice_IceBottomRight,
		TerrainResources::Ice_IceLeft,
		TerrainResources::Ice_IceRight,
		Color4B(11, 30, 39, 255)))
{
}

IceTerrainDeserializer::~IceTerrainDeserializer()
{
}
