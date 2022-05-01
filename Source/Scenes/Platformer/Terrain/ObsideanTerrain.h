#pragma once

#include "Engine/Terrain/TerrainObject.h"

class ObsideanTerrain : public TerrainObject
{
public:
	static ObsideanTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	ObsideanTerrain(cocos2d::ValueMap& properties);
	virtual ~ObsideanTerrain();

private:
	typedef TerrainObject super;
};
