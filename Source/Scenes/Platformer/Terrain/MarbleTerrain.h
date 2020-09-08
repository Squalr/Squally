#pragma once

#include "Engine/Terrain/TerrainObject.h"

class MarbleTerrain : public TerrainObject
{
public:
	static MarbleTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	MarbleTerrain(cocos2d::ValueMap& properties);
	virtual ~MarbleTerrain();

private:
	typedef TerrainObject super;
};
