#pragma once

#include "Engine/Terrain/TerrainObject.h"

class GrassTerrain : public TerrainObject
{
public:
	static GrassTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	GrassTerrain(cocos2d::ValueMap& properties);
	virtual ~GrassTerrain();

private:
	typedef TerrainObject super;
};
