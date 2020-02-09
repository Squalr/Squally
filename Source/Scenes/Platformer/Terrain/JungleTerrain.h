#pragma once

#include "Engine/Terrain/TerrainObject.h"

class JungleTerrain : public TerrainObject
{
public:
	static JungleTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

protected:
	JungleTerrain(cocos2d::ValueMap& properties);
	virtual ~JungleTerrain();

private:
	typedef TerrainObject super;
};
