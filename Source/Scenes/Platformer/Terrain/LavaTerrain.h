#pragma once

#include "Engine/Terrain/TerrainObject.h"

class LavaTerrain : public TerrainObject
{
public:
	static LavaTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	LavaTerrain(cocos2d::ValueMap& properties);
	virtual ~LavaTerrain();

private:
	typedef TerrainObject super;
};
