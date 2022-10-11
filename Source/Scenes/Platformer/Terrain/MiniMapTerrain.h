#pragma once

#include "Engine/Terrain/MiniMapTerrainObject.h"

class MiniMapTerrain : public MiniMapTerrainObject
{
public:
	static MiniMapTerrain* create(cocos2d::ValueMap& properties, cocos2d::Color4B drawColor);

	static const std::string MapKey;

protected:
	MiniMapTerrain(cocos2d::ValueMap& properties, cocos2d::Color4B drawColor);
	virtual ~MiniMapTerrain();

private:
	typedef MiniMapTerrainObject super;
};
