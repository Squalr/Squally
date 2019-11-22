#pragma once

#include "Engine/Terrain/TerrainObject.h"

class BlueGrassTerrain : public TerrainObject
{
public:
	static BlueGrassTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

private:
	typedef TerrainObject super;

	BlueGrassTerrain(cocos2d::ValueMap& properties);
	~BlueGrassTerrain();
};
