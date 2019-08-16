#pragma once

#include "Engine/Terrain/TerrainObject.h"

class IceTerrain : public TerrainObject
{
public:
	static IceTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainTypeIce;

private:
	typedef TerrainObject super;
	
	IceTerrain(cocos2d::ValueMap& properties);
	~IceTerrain();
};
