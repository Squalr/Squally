#pragma once

#include "Engine/Terrain/TerrainObject.h"

class MarbleTerrain : public TerrainObject
{
public:
	static MarbleTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

private:
	typedef TerrainObject super;
	
	MarbleTerrain(cocos2d::ValueMap& properties);
	~MarbleTerrain();
};
