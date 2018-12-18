////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class SnowFiend : public PlatformerEnemy
{
public:
	static SnowFiend* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeySnowFiend;

private:
	SnowFiend(cocos2d::ValueMap* initProperties);
	~SnowFiend();
};
