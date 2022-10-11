#pragma once

#include "Engine/Terrain/TerrainObject.h"

class MarbleGrassTerrain : public TerrainObject
{
public:
	static MarbleGrassTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const cocos2d::Color4B FillColor;
	static const cocos2d::Color4B MiniMapColor;

protected:
	MarbleGrassTerrain(cocos2d::ValueMap& properties);
	virtual ~MarbleGrassTerrain();

private:
	typedef TerrainObject super;
};
