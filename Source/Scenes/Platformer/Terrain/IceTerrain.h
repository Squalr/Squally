#pragma once

#include "Engine/Terrain/TerrainObject.h"

class IceTerrain : public TerrainObject
{
public:
	static IceTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	IceTerrain(cocos2d::ValueMap& properties);
	virtual ~IceTerrain();

private:
	typedef TerrainObject super;
};
