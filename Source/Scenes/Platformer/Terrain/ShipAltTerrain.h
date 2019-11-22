#pragma once

#include "Engine/Terrain/TerrainObject.h"

class ShipAltTerrain : public TerrainObject
{
public:
	static ShipAltTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

private:
	typedef TerrainObject super;

	ShipAltTerrain(cocos2d::ValueMap& properties);
	~ShipAltTerrain();
};
