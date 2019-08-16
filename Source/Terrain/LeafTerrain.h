#pragma once

#include "Engine/Terrain/TerrainObject.h"

class LeafTerrain : public TerrainObject
{
public:
	static LeafTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainTypeLeaf;

private:
	typedef TerrainObject super;

	LeafTerrain(cocos2d::ValueMap& properties);
	~LeafTerrain();
};
