#pragma once

#include "Engine/Terrain/TerrainObject.h"

class WoodTerrain : public TerrainObject
{
public:
	static WoodTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	WoodTerrain(cocos2d::ValueMap& properties);
	virtual ~WoodTerrain();

private:
	typedef TerrainObject super;
};
