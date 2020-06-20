#pragma once

#include "Engine/Terrain/TerrainObject.h"

class RuinsGrayThickTerrain : public TerrainObject
{
public:
	static RuinsGrayThickTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	RuinsGrayThickTerrain(cocos2d::ValueMap& properties);
	virtual ~RuinsGrayThickTerrain();

private:
	typedef TerrainObject super;
};
