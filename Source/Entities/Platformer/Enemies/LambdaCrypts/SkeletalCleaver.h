////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class SkeletalCleaver : public PlatformerEnemy
{
public:
	static SkeletalCleaver* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeySkeletalCleaver;

private:
	SkeletalCleaver(cocos2d::ValueMap& initProperties);
	~SkeletalCleaver();
};
