#pragma once

#include "Engine/Terrain/TerrainObject.h"

class BlueGrassTerrain : public TerrainObject
{
public:
	static BlueGrassTerrain* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTerrainTypeBlueGrass;

private:
	typedef TerrainObject super;

	BlueGrassTerrain(cocos2d::ValueMap& initProperties);
	~BlueGrassTerrain();
};
