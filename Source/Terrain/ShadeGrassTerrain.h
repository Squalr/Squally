#pragma once

#include "Engine/Terrain/TerrainObject.h"

class ShadeGrassTerrain : public TerrainObject
{
public:
	static ShadeGrassTerrain* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTerrainTypeShadeGrass;

private:
	typedef TerrainObject super;
	
	ShadeGrassTerrain(cocos2d::ValueMap& initProperties);
	~ShadeGrassTerrain();
};
