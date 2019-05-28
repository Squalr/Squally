#include "IceTerrainDeserializer.h"

#include "Engine/GlobalDirector.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string IceTerrainDeserializer::MapKeyTerrainTypeIce = "ice";
IceTerrainDeserializer* IceTerrainDeserializer::instance = nullptr;

void IceTerrainDeserializer::registerGlobalNode()
{
	if (IceTerrainDeserializer::instance == nullptr)
	{
		IceTerrainDeserializer::instance = new IceTerrainDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(IceTerrainDeserializer::instance);
	}
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
