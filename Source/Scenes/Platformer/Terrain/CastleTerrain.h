#pragma once

#include "Engine/Terrain/TerrainObject.h"

class CastleTerrain : public TerrainObject
{
public:
	static CastleTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

private:
	typedef TerrainObject super;
	
	CastleTerrain(cocos2d::ValueMap& properties);
	~CastleTerrain();
};
