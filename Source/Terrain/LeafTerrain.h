#pragma once

#include "Engine/Terrain/TerrainObject.h"

class LeafTerrain : public TerrainObject
{
public:
	static LeafTerrain* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTerrainTypeLeaf;

private:
	typedef TerrainObject super;

	LeafTerrain(cocos2d::ValueMap& initProperties);
	~LeafTerrain();
};
