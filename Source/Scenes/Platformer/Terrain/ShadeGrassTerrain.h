#pragma once

#include "Engine/Terrain/TerrainObject.h"

class ShadeGrassTerrain : public TerrainObject
{
public:
	static ShadeGrassTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	ShadeGrassTerrain(cocos2d::ValueMap& properties);
	virtual ~ShadeGrassTerrain();

private:
	typedef TerrainObject super;
};
