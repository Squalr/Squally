#pragma once

#include "Engine/Terrain/TerrainObject.h"

class BlueGrassTerrain : public TerrainObject
{
public:
	static BlueGrassTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	BlueGrassTerrain(cocos2d::ValueMap& properties);
	virtual ~BlueGrassTerrain();

private:
	typedef TerrainObject super;
};
