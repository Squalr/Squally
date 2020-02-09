#pragma once

#include "Engine/Terrain/TerrainObject.h"

class DarkGrassTerrain : public TerrainObject
{
public:
	static DarkGrassTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

protected:
	DarkGrassTerrain(cocos2d::ValueMap& properties);
	virtual ~DarkGrassTerrain();

private:
	typedef TerrainObject super;
};
