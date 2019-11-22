#pragma once

#include "Engine/Terrain/TerrainObject.h"

class TempleTerrain : public TerrainObject
{
public:
	static TempleTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

private:
	typedef TerrainObject super;

	TempleTerrain(cocos2d::ValueMap& properties);
	~TempleTerrain();
};
