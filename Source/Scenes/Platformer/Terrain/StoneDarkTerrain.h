#pragma once

#include "Engine/Terrain/TerrainObject.h"

class StoneDarkTerrain : public TerrainObject
{
public:
	static StoneDarkTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	StoneDarkTerrain(cocos2d::ValueMap& properties);
	virtual ~StoneDarkTerrain();

private:
	typedef TerrainObject super;
};
