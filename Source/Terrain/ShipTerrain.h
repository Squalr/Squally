#pragma once

#include "Engine/Terrain/TerrainObject.h"

class ShipTerrain : public TerrainObject
{
public:
	static ShipTerrain* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTerrainTypeShip;

private:
	typedef TerrainObject super;

	ShipTerrain(cocos2d::ValueMap& initProperties);
	~ShipTerrain();
};
