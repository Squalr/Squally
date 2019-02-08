////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class EarthGolem : public PlatformerEnemy
{
public:
	static EarthGolem* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyEarthGolem;

private:
	EarthGolem(cocos2d::ValueMap& initProperties);
	~EarthGolem();
};
