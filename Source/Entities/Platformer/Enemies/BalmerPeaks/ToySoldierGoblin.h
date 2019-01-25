////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class ToySoldierGoblin : public PlatformerEnemy
{
public:
	static ToySoldierGoblin* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyToySoldierGoblin;

private:
	ToySoldierGoblin(cocos2d::ValueMap* initProperties);
	~ToySoldierGoblin();
};
