#pragma once

#include "Engine/Terrain/TerrainObject.h"

class RuinsGrayDarkTerrain : public TerrainObject
{
public:
	static RuinsGrayDarkTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	RuinsGrayDarkTerrain(cocos2d::ValueMap& properties);
	virtual ~RuinsGrayDarkTerrain();

private:
	typedef TerrainObject super;
};
