#pragma once

#include "Engine/Terrain/TerrainObject.h"

class MarbleDarkTerrain : public TerrainObject
{
public:
	static MarbleDarkTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

private:
	typedef TerrainObject super;
	
	MarbleDarkTerrain(cocos2d::ValueMap& properties);
	~MarbleDarkTerrain();
};
