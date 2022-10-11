#pragma once

#include "Engine/Terrain/TerrainObject.h"

class MarbleDarkTerrain : public TerrainObject
{
public:
	static MarbleDarkTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	MarbleDarkTerrain(cocos2d::ValueMap& properties);
	virtual ~MarbleDarkTerrain();

private:
	typedef TerrainObject super;
};
