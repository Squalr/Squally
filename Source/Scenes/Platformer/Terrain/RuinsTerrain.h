#pragma once

#include "Engine/Terrain/TerrainObject.h"

class RuinsTerrain : public TerrainObject
{
public:
	static RuinsTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	RuinsTerrain(cocos2d::ValueMap& properties);
	virtual ~RuinsTerrain();

private:
	typedef TerrainObject super;
};
