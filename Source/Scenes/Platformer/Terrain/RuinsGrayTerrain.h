#pragma once

#include "Engine/Terrain/TerrainObject.h"

class RuinsGrayTerrain : public TerrainObject
{
public:
	static RuinsGrayTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	RuinsGrayTerrain(cocos2d::ValueMap& properties);
	virtual ~RuinsGrayTerrain();

private:
	typedef TerrainObject super;
};
