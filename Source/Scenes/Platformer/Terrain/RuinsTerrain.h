#pragma once

#include "Engine/Terrain/TerrainObject.h"

class RuinsTerrain : public TerrainObject
{
public:
	static RuinsTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	RuinsTerrain(cocos2d::ValueMap& properties);
	virtual ~RuinsTerrain();

private:
	typedef TerrainObject super;
};
