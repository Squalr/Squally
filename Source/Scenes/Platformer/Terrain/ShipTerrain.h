#pragma once

#include "Engine/Terrain/TerrainObject.h"

class ShipTerrain : public TerrainObject
{
public:
	static ShipTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	ShipTerrain(cocos2d::ValueMap& properties);
	virtual ~ShipTerrain();

private:
	typedef TerrainObject super;
};
