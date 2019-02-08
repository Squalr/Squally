////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class EarthElemental : public PlatformerEnemy
{
public:
	static EarthElemental* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyEarthElemental;

private:
	EarthElemental(cocos2d::ValueMap& initProperties);
	~EarthElemental();
};
