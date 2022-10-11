#pragma once

#include "Engine/Terrain/TerrainObject.h"

class VoidTerrain : public TerrainObject
{
public:
	static VoidTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	VoidTerrain(cocos2d::ValueMap& properties);
	virtual ~VoidTerrain();

private:
	typedef TerrainObject super;
};
