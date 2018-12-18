////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class SkeletalNecromancer : public PlatformerEnemy
{
public:
	static SkeletalNecromancer* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeySkeletalNecromancer;

private:
	SkeletalNecromancer(cocos2d::ValueMap* initProperties);
	~SkeletalNecromancer();
};
