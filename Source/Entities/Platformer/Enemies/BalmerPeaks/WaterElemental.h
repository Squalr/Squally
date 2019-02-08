////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class WaterElemental : public PlatformerEnemy
{
public:
	static WaterElemental* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyWaterElemental;

private:
	WaterElemental(cocos2d::ValueMap& initProperties);
	~WaterElemental();
};
