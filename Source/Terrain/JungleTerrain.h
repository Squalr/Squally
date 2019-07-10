#pragma once

#include "Engine/Terrain/TerrainObject.h"

class JungleTerrain : public TerrainObject
{
public:
	static JungleTerrain* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTerrainTypeJungle;

private:
	typedef TerrainObject super;
	
	JungleTerrain(cocos2d::ValueMap& initProperties);
	~JungleTerrain();
};
