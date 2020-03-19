#pragma once

#include "Engine/Terrain/TerrainObject.h"

class DryTerrain : public TerrainObject
{
public:
	static DryTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	DryTerrain(cocos2d::ValueMap& properties);
	virtual ~DryTerrain();

private:
	typedef TerrainObject super;
};
