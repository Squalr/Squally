#pragma once

#include "Engine/Terrain/TerrainObject.h"

class ShipTerrain : public TerrainObject
{
public:
	static ShipTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

private:
	typedef TerrainObject super;

	ShipTerrain(cocos2d::ValueMap& properties);
	~ShipTerrain();
};
