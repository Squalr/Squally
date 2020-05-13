#pragma once

#include "Engine/Terrain/TerrainObject.h"

class RuinsThickTerrain : public TerrainObject
{
public:
	static RuinsThickTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	RuinsThickTerrain(cocos2d::ValueMap& properties);
	virtual ~RuinsThickTerrain();

private:
	typedef TerrainObject super;
};
