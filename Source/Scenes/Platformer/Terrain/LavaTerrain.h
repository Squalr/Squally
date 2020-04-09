#pragma once

#include "Engine/Terrain/TerrainObject.h"

class LavaTerrain : public TerrainObject
{
public:
	static LavaTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	LavaTerrain(cocos2d::ValueMap& properties);
	virtual ~LavaTerrain();

private:
	typedef TerrainObject super;
};
