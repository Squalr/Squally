#pragma once

#include "Engine/Terrain/TerrainObject.h"

class MarbleDarkTerrain : public TerrainObject
{
public:
	static MarbleDarkTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

protected:
	MarbleDarkTerrain(cocos2d::ValueMap& properties);
	virtual ~MarbleDarkTerrain();

private:
	typedef TerrainObject super;
};
