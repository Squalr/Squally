#pragma once

#include "Engine/Terrain/TerrainObject.h"

class CastleTerrain : public TerrainObject
{
public:
	static CastleTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

protected:
	CastleTerrain(cocos2d::ValueMap& properties);
	virtual ~CastleTerrain();

private:
	typedef TerrainObject super;
};
