#pragma once

#include "Engine/Terrain/TerrainObject.h"

class TempleDarkTerrain : public TerrainObject
{
public:
	static TempleDarkTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	TempleDarkTerrain(cocos2d::ValueMap& properties);
	virtual ~TempleDarkTerrain();

private:
	typedef TerrainObject super;
};
