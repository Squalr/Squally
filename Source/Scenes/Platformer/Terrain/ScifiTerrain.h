#pragma once

#include "Engine/Terrain/TerrainObject.h"

class ScifiTerrain : public TerrainObject
{
public:
	static ScifiTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	ScifiTerrain(cocos2d::ValueMap& properties);
	virtual ~ScifiTerrain();

private:
	typedef TerrainObject super;
};
