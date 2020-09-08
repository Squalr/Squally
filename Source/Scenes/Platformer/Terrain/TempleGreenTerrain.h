#pragma once

#include "Engine/Terrain/TerrainObject.h"

class TempleGreenTerrain : public TerrainObject
{
public:
	static TempleGreenTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	TempleGreenTerrain(cocos2d::ValueMap& properties);
	virtual ~TempleGreenTerrain();

private:
	typedef TerrainObject super;
};
