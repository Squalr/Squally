#pragma once

#include "Engine/Terrain/TerrainObject.h"

class RailsTerrain : public TerrainObject
{
public:
	static RailsTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	RailsTerrain(cocos2d::ValueMap& properties);
	virtual ~RailsTerrain();

private:
	typedef TerrainObject super;
};
