#pragma once

#include "Engine/Terrain/TerrainObject.h"

class ShadeGrassTerrain : public TerrainObject
{
public:
	static ShadeGrassTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ShadeGrassTerrain(cocos2d::ValueMap& properties);
	virtual ~ShadeGrassTerrain();

private:
	typedef TerrainObject super;
};
