#pragma once
#include "cocos2d.h"

#include "Engine/Terrain/TerrainDeserializer.h"
#include "Resources/TerrainResources.h"

using namespace cocos2d;

class CastleTerrainDeserializer : public TerrainDeserializer
{
public:
	static void registerGlobalNode();

	static const std::string MapKeyTerrainTypeCastle;

private:
	CastleTerrainDeserializer();
	~CastleTerrainDeserializer();

	static CastleTerrainDeserializer* instance;
};
