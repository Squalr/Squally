////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class ForestGolem : public PlatformerEnemy
{
public:
	static ForestGolem* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyForestGolem;

private:
	ForestGolem(cocos2d::ValueMap* initProperties);
	~ForestGolem();
};
