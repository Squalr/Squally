#pragma once

#include "Engine/Terrain/TerrainObject.h"

class MinesTerrain : public TerrainObject
{
public:
	static MinesTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	MinesTerrain(cocos2d::ValueMap& properties);
	virtual ~MinesTerrain();

private:
	typedef TerrainObject super;
};
