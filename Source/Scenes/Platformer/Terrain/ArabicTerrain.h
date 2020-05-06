#pragma once

#include "Engine/Terrain/TerrainObject.h"

class ArabicTerrain : public TerrainObject
{
public:
	static ArabicTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ArabicTerrain(cocos2d::ValueMap& properties);
	virtual ~ArabicTerrain();

private:
	typedef TerrainObject super;
};
