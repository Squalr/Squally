#pragma once

#include "Engine/Terrain/TerrainObject.h"

class TrailTerrain : public TerrainObject
{
public:
	static TrailTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	TrailTerrain(cocos2d::ValueMap& properties);
	virtual ~TrailTerrain();

private:
	typedef TerrainObject super;
};
