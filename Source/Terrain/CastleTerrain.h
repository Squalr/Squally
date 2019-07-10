#pragma once

#include "Engine/Terrain/TerrainObject.h"

class CastleTerrain : public TerrainObject
{
public:
	static CastleTerrain* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTerrainTypeCastle;

private:
	typedef TerrainObject super;
	
	CastleTerrain(cocos2d::ValueMap& initProperties);
	~CastleTerrain();
};
