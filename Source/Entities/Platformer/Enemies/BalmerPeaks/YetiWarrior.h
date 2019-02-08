////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class YetiWarrior : public PlatformerEnemy
{
public:
	static YetiWarrior* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyYetiWarrior;

private:
	YetiWarrior(cocos2d::ValueMap& initProperties);
	~YetiWarrior();
};
