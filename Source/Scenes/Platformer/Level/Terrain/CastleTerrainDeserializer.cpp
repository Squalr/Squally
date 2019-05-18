#include "CastleTerrainDeserializer.h"

#include "Engine/GlobalDirector.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string CastleTerrainDeserializer::MapKeyTerrainTypeCastle = "castle";
CastleTerrainDeserializer* CastleTerrainDeserializer::instance = nullptr;

void CastleTerrainDeserializer::registerGlobalNode()
{
	if (CastleTerrainDeserializer::instance == nullptr)
	{
		CastleTerrainDeserializer::instance = new CastleTerrainDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(CastleTerrainDeserializer::instance);
	}
}

CastleTerrainDeserializer::CastleTerrainDeserializer() : TerrainDeserializer(
	TerrainObject::TerrainData(
		0.5f,
		CastleTerrainDeserializer::MapKeyTerrainTypeCastle,
		TerrainResources::Castle_CastleTexture,
		TerrainResources::Castle_Castle,
		TerrainResources::Castle_CastleTopLeft,
		TerrainResources::Castle_CastleTopRight,
		TerrainResources::Castle_CastleBottom,
		TerrainResources::Castle_CastleBottomLeft,
		TerrainResources::Castle_CastleBottomRight,
		TerrainResources::Castle_CastleLeft,
		TerrainResources::Castle_CastleRight,
		Color4B(11, 30, 39, 255)))
{
}

CastleTerrainDeserializer::~CastleTerrainDeserializer()
{
}
