#pragma once

#include "Engine/Terrain/TerrainObject.h"

class MarbleGrassTerrain : public TerrainObject
{
public:
	static MarbleGrassTerrain* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTerrainTypeMarbleGrass;

private:
	typedef TerrainObject super;
	
	MarbleGrassTerrain(cocos2d::ValueMap& initProperties);
	~MarbleGrassTerrain();
};
