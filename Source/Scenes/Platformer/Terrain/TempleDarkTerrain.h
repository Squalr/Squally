#pragma once

#include "Engine/Terrain/TerrainObject.h"

class TempleDarkTerrain : public TerrainObject
{
public:
	static TempleDarkTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	TempleDarkTerrain(cocos2d::ValueMap& properties);
	virtual ~TempleDarkTerrain();

private:
	typedef TerrainObject super;
};
