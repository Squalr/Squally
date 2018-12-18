////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class DemonWarrior : public PlatformerEnemy
{
public:
	static DemonWarrior* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyDemonWarrior;

private:
	DemonWarrior(cocos2d::ValueMap* initProperties);
	~DemonWarrior();
};
