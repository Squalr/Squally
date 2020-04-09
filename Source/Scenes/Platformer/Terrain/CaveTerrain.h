#pragma once

#include "Engine/Terrain/TerrainObject.h"

class CaveTerrain : public TerrainObject
{
public:
	static CaveTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CaveTerrain(cocos2d::ValueMap& properties);
	virtual ~CaveTerrain();

private:
	typedef TerrainObject super;
};
