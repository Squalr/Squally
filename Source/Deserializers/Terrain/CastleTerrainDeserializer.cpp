#include "CastleTerrainDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string CastleTerrainDeserializer::MapKeyTerrainTypeCastle = "castle";

CastleTerrainDeserializer* CastleTerrainDeserializer::create()
{
	CastleTerrainDeserializer* instance = new CastleTerrainDeserializer();

	instance->autorelease();

	return instance;
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
