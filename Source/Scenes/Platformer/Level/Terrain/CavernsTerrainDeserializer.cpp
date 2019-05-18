#include "CavernsTerrainDeserializer.h"

#include "Engine/GlobalDirector.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string CavernsTerrainDeserializer::MapKeyTerrainTypeCaverns = "caverns";
CavernsTerrainDeserializer* CavernsTerrainDeserializer::instance = nullptr;

void CavernsTerrainDeserializer::registerGlobalNode()
{
	if (CavernsTerrainDeserializer::instance == nullptr)
	{
		CavernsTerrainDeserializer::instance = new CavernsTerrainDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(CavernsTerrainDeserializer::instance);
	}
}

CavernsTerrainDeserializer::CavernsTerrainDeserializer() : TerrainDeserializer(
	TerrainObject::TerrainData(
		0.5f,
		CavernsTerrainDeserializer::MapKeyTerrainTypeCaverns,
		TerrainResources::Caverns_CavernsTexture,
		TerrainResources::Caverns_Caverns,
		TerrainResources::Caverns_CavernsTopLeft,
		TerrainResources::Caverns_CavernsTopRight,
		TerrainResources::Caverns_CavernsBottom,
		TerrainResources::Caverns_CavernsBottomLeft,
		TerrainResources::Caverns_CavernsBottomRight,
		TerrainResources::Caverns_CavernsLeft,
		TerrainResources::Caverns_CavernsRight,
		Color4B(11, 30, 39, 255)))
{
}

CavernsTerrainDeserializer::~CavernsTerrainDeserializer()
{
}
