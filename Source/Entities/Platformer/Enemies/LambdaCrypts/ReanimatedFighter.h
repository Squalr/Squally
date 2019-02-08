////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class ReanimatedFighter : public PlatformerEnemy
{
public:
	static ReanimatedFighter* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyReanimatedFighter;

private:
	ReanimatedFighter(cocos2d::ValueMap& initProperties);
	~ReanimatedFighter();
};
