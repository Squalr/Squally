#pragma once

#include "Engine/Terrain/TerrainObject.h"

class VinesTerrain : public TerrainObject
{
public:
	static VinesTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	VinesTerrain(cocos2d::ValueMap& properties);
	virtual ~VinesTerrain();

private:
	typedef TerrainObject super;
};
