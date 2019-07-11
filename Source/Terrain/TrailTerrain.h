#pragma once

#include "Engine/Terrain/TerrainObject.h"

class TrailTerrain : public TerrainObject
{
public:
	static TrailTerrain* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTerrainTypeTrail;

private:
	typedef TerrainObject super;

	TrailTerrain(cocos2d::ValueMap& initProperties);
	~TrailTerrain();
};
