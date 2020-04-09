#pragma once

#include "Engine/Terrain/TerrainObject.h"

class TempleTerrain : public TerrainObject
{
public:
	static TempleTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	TempleTerrain(cocos2d::ValueMap& properties);
	virtual ~TempleTerrain();

private:
	typedef TerrainObject super;
};
