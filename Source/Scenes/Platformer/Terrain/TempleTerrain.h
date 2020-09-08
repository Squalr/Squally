#pragma once

#include "Engine/Terrain/TerrainObject.h"

class TempleTerrain : public TerrainObject
{
public:
	static TempleTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	TempleTerrain(cocos2d::ValueMap& properties);
	virtual ~TempleTerrain();

private:
	typedef TerrainObject super;
};
