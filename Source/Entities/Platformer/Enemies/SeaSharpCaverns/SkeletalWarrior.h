////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class SkeletalWarrior : public PlatformerEnemy
{
public:
	static SkeletalWarrior* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeySkeletalWarrior;

private:
	SkeletalWarrior(cocos2d::ValueMap& initProperties);
	~SkeletalWarrior();
};
