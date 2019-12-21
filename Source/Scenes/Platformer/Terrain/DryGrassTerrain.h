#pragma once

#include "Engine/Terrain/TerrainObject.h"

class DryGrassTerrain : public TerrainObject
{
public:
	static DryGrassTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

private:
	typedef TerrainObject super;

	DryGrassTerrain(cocos2d::ValueMap& properties);
	~DryGrassTerrain();
};
