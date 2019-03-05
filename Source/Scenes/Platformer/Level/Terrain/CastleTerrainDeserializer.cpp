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
		TerrainResources::CastleTexture,
		TerrainResources::Castle,
		TerrainResources::CastleTopLeft,
		TerrainResources::CastleTopRight,
		TerrainResources::CastleBottom,
		TerrainResources::CastleBottomLeft,
		TerrainResources::CastleBottomRight,
		TerrainResources::CastleLeft,
		TerrainResources::CastleRight,
		Color4B(11, 30, 39, 255)))
{
}

CastleTerrainDeserializer::~CastleTerrainDeserializer()
{
}
