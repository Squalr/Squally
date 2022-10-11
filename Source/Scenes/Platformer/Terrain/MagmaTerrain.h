#pragma once

#include "Engine/Terrain/TerrainObject.h"

class MagmaTerrain : public TerrainObject
{
public:
	static MagmaTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	MagmaTerrain(cocos2d::ValueMap& properties);
	virtual ~MagmaTerrain();

private:
	typedef TerrainObject super;
};
