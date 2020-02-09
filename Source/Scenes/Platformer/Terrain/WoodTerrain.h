#pragma once

#include "Engine/Terrain/TerrainObject.h"

class WoodTerrain : public TerrainObject
{
public:
	static WoodTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

protected:
	WoodTerrain(cocos2d::ValueMap& properties);
	virtual ~WoodTerrain();

private:
	typedef TerrainObject super;
};
