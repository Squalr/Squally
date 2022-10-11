#pragma once

#include "Engine/Terrain/TerrainObject.h"

class DryTerrain : public TerrainObject
{
public:
	static DryTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	DryTerrain(cocos2d::ValueMap& properties);
	virtual ~DryTerrain();

private:
	typedef TerrainObject super;
};
