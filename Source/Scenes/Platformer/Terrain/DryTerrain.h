#pragma once

#include "Engine/Terrain/TerrainObject.h"

class DryTerrain : public TerrainObject
{
public:
	static DryTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

private:
	typedef TerrainObject super;

	DryTerrain(cocos2d::ValueMap& properties);
	~DryTerrain();
};
