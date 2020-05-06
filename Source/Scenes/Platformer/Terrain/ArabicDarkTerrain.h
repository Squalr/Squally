#pragma once

#include "Engine/Terrain/TerrainObject.h"

class ArabicDarkTerrain : public TerrainObject
{
public:
	static ArabicDarkTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ArabicDarkTerrain(cocos2d::ValueMap& properties);
	virtual ~ArabicDarkTerrain();

private:
	typedef TerrainObject super;
};
