#pragma once

#include "Engine/Terrain/TerrainObject.h"

class InvisibleTerrain : public TerrainObject
{
public:
	static InvisibleTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	InvisibleTerrain(cocos2d::ValueMap& properties);
	virtual ~InvisibleTerrain();

private:
	typedef TerrainObject super;
};
