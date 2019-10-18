#pragma once

#include "Engine/Terrain/TerrainObject.h"

class LavaTerrain : public TerrainObject
{
public:
	static LavaTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainTypeLava;

private:
	typedef TerrainObject super;

	LavaTerrain(cocos2d::ValueMap& properties);
	~LavaTerrain();
};
