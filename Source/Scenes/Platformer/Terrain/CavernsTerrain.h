#pragma once

#include "Engine/Terrain/TerrainObject.h"

class CavernsTerrain : public TerrainObject
{
public:
	static CavernsTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	CavernsTerrain(cocos2d::ValueMap& properties);
	virtual ~CavernsTerrain();

private:
	typedef TerrainObject super;
};
