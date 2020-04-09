#pragma once

#include "Engine/Terrain/TerrainObject.h"

class BlueGrassTerrain : public TerrainObject
{
public:
	static BlueGrassTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	BlueGrassTerrain(cocos2d::ValueMap& properties);
	virtual ~BlueGrassTerrain();

private:
	typedef TerrainObject super;
};
