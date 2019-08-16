#pragma once

#include "Engine/Terrain/TerrainObject.h"

class FrostTerrain : public TerrainObject
{
public:
	static FrostTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainTypeFrost;

private:
	typedef TerrainObject super;
	
	FrostTerrain(cocos2d::ValueMap& properties);
	~FrostTerrain();
};
