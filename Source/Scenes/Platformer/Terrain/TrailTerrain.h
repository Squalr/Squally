#pragma once

#include "Engine/Terrain/TerrainObject.h"

class TrailTerrain : public TerrainObject
{
public:
	static TrailTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

protected:
	TrailTerrain(cocos2d::ValueMap& properties);
	virtual ~TrailTerrain();

private:
	typedef TerrainObject super;
};
