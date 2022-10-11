#pragma once

#include "Engine/Terrain/TerrainObject.h"

class JungleTerrain : public TerrainObject
{
public:
	static JungleTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	JungleTerrain(cocos2d::ValueMap& properties);
	virtual ~JungleTerrain();

private:
	typedef TerrainObject super;
};
