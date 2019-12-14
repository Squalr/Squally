#pragma once

#include "Engine/Terrain/TerrainObject.h"

class TempleGreenTerrain : public TerrainObject
{
public:
	static TempleGreenTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

private:
	typedef TerrainObject super;

	TempleGreenTerrain(cocos2d::ValueMap& properties);
	~TempleGreenTerrain();
};
