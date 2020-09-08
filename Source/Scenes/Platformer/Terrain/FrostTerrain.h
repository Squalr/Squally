#pragma once

#include "Engine/Terrain/TerrainObject.h"

class FrostTerrain : public TerrainObject
{
public:
	static FrostTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	FrostTerrain(cocos2d::ValueMap& properties);
	virtual ~FrostTerrain();

private:
	typedef TerrainObject super;
};
