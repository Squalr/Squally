#pragma once

#include "Engine/Terrain/TerrainObject.h"

class TempleGreenTerrain : public TerrainObject
{
public:
	static TempleGreenTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	TempleGreenTerrain(cocos2d::ValueMap& properties);
	virtual ~TempleGreenTerrain();

private:
	typedef TerrainObject super;
};
