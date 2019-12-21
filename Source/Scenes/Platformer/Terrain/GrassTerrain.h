#pragma once

#include "Engine/Terrain/TerrainObject.h"

class GrassTerrain : public TerrainObject
{
public:
	static GrassTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

private:
	typedef TerrainObject super;
	GrassTerrain(cocos2d::ValueMap& properties);
	~GrassTerrain();

	static GrassTerrain* instance;
};
