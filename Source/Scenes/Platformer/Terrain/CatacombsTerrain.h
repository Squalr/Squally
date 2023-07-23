#pragma once

#include "Engine/Terrain/TerrainObject.h"

class CatacombsTerrain : public TerrainObject
{
public:
	static CatacombsTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	CatacombsTerrain(cocos2d::ValueMap& properties);
	virtual ~CatacombsTerrain();

private:
	typedef TerrainObject super;
};
