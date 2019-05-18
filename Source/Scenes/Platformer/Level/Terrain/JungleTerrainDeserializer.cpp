#include "JungleTerrainDeserializer.h"

#include "Engine/GlobalDirector.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string JungleTerrainDeserializer::MapKeyTerrainTypeJungle = "jungle";
JungleTerrainDeserializer* JungleTerrainDeserializer::instance = nullptr;

void JungleTerrainDeserializer::registerGlobalNode()
{
	if (JungleTerrainDeserializer::instance == nullptr)
	{
		JungleTerrainDeserializer::instance = new JungleTerrainDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(JungleTerrainDeserializer::instance);
	}
}

JungleTerrainDeserializer::JungleTerrainDeserializer() : TerrainDeserializer(
	TerrainObject::TerrainData(
		0.5f,
		JungleTerrainDeserializer::MapKeyTerrainTypeJungle,
		TerrainResources::Jungle_JungleTexture,
		TerrainResources::Jungle_Jungle,
		TerrainResources::Jungle_JungleTopLeft,
		TerrainResources::Jungle_JungleTopRight,
		TerrainResources::Jungle_JungleBottom,
		TerrainResources::Jungle_JungleBottomLeft,
		TerrainResources::Jungle_JungleBottomRight,
		TerrainResources::Jungle_JungleLeft,
		TerrainResources::Jungle_JungleRight,
		Color4B(11, 30, 39, 255)))
{
}

JungleTerrainDeserializer::~JungleTerrainDeserializer()
{
}
