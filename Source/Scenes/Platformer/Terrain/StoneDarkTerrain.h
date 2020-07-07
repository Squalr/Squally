#pragma once

#include "Engine/Terrain/TerrainObject.h"

class StoneDarkTerrain : public TerrainObject
{
public:
	static StoneDarkTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	StoneDarkTerrain(cocos2d::ValueMap& properties);
	virtual ~StoneDarkTerrain();

private:
	typedef TerrainObject super;
};
