#pragma once

#include "Engine/Terrain/TerrainObject.h"

class MarbleTerrain : public TerrainObject
{
public:
	static MarbleTerrain* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTerrainTypeMarble;

private:
	typedef TerrainObject super;
	
	MarbleTerrain(cocos2d::ValueMap& initProperties);
	~MarbleTerrain();
};
