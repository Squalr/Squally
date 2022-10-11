#pragma once

#include "Engine/Terrain/TerrainObject.h"

class CastleTerrain : public TerrainObject
{
public:
	static CastleTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	CastleTerrain(cocos2d::ValueMap& properties);
	virtual ~CastleTerrain();

private:
	typedef TerrainObject super;
};
