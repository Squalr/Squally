#pragma once

#include "Engine/Terrain/TerrainObject.h"

class FrostTerrain : public TerrainObject
{
public:
	static FrostTerrain* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTerrainTypeFrost;

private:
	typedef TerrainObject super;
	
	FrostTerrain(cocos2d::ValueMap& initProperties);
	~FrostTerrain();
};
