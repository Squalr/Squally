#pragma once

#include "Engine/Maps/GameObject.h"

class TerrainHole : public GameObject
{
public:
	static TerrainHole* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string TerrainHoleTag;
	
protected:
	TerrainHole(cocos2d::ValueMap& properties);
	virtual ~TerrainHole();

private:
	typedef GameObject super;
};
