#pragma once

#include "Engine/Terrain/TerrainObject.h"

class CavernsTerrain : public TerrainObject
{
public:
	static CavernsTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainTypeCaverns;

private:
	typedef TerrainObject super;

	CavernsTerrain(cocos2d::ValueMap& properties);
	~CavernsTerrain();
};
