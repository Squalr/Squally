#pragma once

#include "Engine/Terrain/TerrainObject.h"

class FrostTerrain : public TerrainObject
{
public:
	static FrostTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

protected:
	FrostTerrain(cocos2d::ValueMap& properties);
	virtual ~FrostTerrain();

private:
	typedef TerrainObject super;
};
