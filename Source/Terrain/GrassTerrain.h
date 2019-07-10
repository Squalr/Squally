#pragma once

#include "Engine/Terrain/TerrainObject.h"

class GrassTerrain : public TerrainObject
{
public:
	static GrassTerrain* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTerrainTypeGrass;

private:
	typedef TerrainObject super;
	GrassTerrain(cocos2d::ValueMap& initProperties);
	~GrassTerrain();

	static GrassTerrain* instance;
};
