////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class AnubisWarrior : public PlatformerEnemy
{
public:
	static AnubisWarrior* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyAnubisWarrior;

private:
	AnubisWarrior(cocos2d::ValueMap& initProperties);
	~AnubisWarrior();
};
