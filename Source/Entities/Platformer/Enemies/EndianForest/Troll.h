////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Troll : public PlatformerEnemy
{
public:
	static Troll* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyTroll;

private:
	Troll(cocos2d::ValueMap* initProperties);
	~Troll();
};
