////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LionMan : public PlatformerEnemy
{
public:
	static LionMan* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyLionMan;

private:
	LionMan(cocos2d::ValueMap& initProperties);
	~LionMan();
};
