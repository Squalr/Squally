#pragma once

#include "Engine/Terrain/TerrainObject.h"

class WoodTerrain : public TerrainObject
{
public:
	static WoodTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainTypeWood;

private:
	typedef TerrainObject super;

	WoodTerrain(cocos2d::ValueMap& properties);
	~WoodTerrain();
};
