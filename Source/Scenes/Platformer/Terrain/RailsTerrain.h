#pragma once

#include "Engine/Terrain/TerrainObject.h"

class RailsTerrain : public TerrainObject
{
public:
	static RailsTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	RailsTerrain(cocos2d::ValueMap& properties);
	virtual ~RailsTerrain();

private:
	typedef TerrainObject super;
};
