#pragma once

#include "Engine/Terrain/TerrainObject.h"

class DarkGrassTerrain : public TerrainObject
{
public:
	static DarkGrassTerrain* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTerrainTypeDarkGrass;

private:
	typedef TerrainObject super;
	
	DarkGrassTerrain(cocos2d::ValueMap& initProperties);
	~DarkGrassTerrain();
};
