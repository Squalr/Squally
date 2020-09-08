#pragma once

#include "Engine/Terrain/TerrainObject.h"

class DryGrassTerrain : public TerrainObject
{
public:
	static DryGrassTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	DryGrassTerrain(cocos2d::ValueMap& properties);
	virtual ~DryGrassTerrain();

private:
	typedef TerrainObject super;
};
