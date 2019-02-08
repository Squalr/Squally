////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class SkeletalArcher : public PlatformerEnemy
{
public:
	static SkeletalArcher* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeySkeletalArcher;

private:
	SkeletalArcher(cocos2d::ValueMap& initProperties);
	~SkeletalArcher();
};
