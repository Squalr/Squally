#pragma once

#include "Engine/Terrain/TerrainObject.h"

class WoodBlackFillTerrain : public TerrainObject
{
public:
	static WoodBlackFillTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	WoodBlackFillTerrain(cocos2d::ValueMap& properties);
	virtual ~WoodBlackFillTerrain();

private:
	typedef TerrainObject super;
};
