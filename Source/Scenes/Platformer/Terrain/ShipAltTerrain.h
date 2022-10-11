#pragma once

#include "Engine/Terrain/TerrainObject.h"

class ShipAltTerrain : public TerrainObject
{
public:
	static ShipAltTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	ShipAltTerrain(cocos2d::ValueMap& properties);
	virtual ~ShipAltTerrain();

private:
	typedef TerrainObject super;
};
