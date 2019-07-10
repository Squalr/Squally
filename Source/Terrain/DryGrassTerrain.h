#pragma once

#include "Engine/Terrain/TerrainObject.h"

class DryGrassTerrain : public TerrainObject
{
public:
	static DryGrassTerrain* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTerrainTypeDryGrass;

private:
	typedef TerrainObject super;

	DryGrassTerrain(cocos2d::ValueMap& initProperties);
	~DryGrassTerrain();
};
