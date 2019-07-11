#pragma once

#include "Engine/Terrain/TerrainObject.h"

class CaveTerrain : public TerrainObject
{
public:
	static CaveTerrain* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTerrainTypeCave;

private:
	typedef TerrainObject super;

	CaveTerrain(cocos2d::ValueMap& initProperties);
	~CaveTerrain();
};
