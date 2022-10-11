#pragma once

#include "Engine/Terrain/TerrainObject.h"

class RuinsThickTerrain : public TerrainObject
{
public:
	static RuinsThickTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	RuinsThickTerrain(cocos2d::ValueMap& properties);
	virtual ~RuinsThickTerrain();

private:
	typedef TerrainObject super;
};
