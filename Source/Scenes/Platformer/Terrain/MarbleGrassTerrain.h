#pragma once

#include "Engine/Terrain/TerrainObject.h"

class MarbleGrassTerrain : public TerrainObject
{
public:
	static MarbleGrassTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

private:
	typedef TerrainObject super;
	
	MarbleGrassTerrain(cocos2d::ValueMap& properties);
	~MarbleGrassTerrain();
};
