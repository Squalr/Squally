#pragma once

#include "Engine/Terrain/TerrainObject.h"

class DryTerrain : public TerrainObject
{
public:
	static DryTerrain* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTerrainTypeDry;

private:
	typedef TerrainObject super;

	DryTerrain(cocos2d::ValueMap& initProperties);
	~DryTerrain();
};
