////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class SkeletalBaron : public PlatformerEnemy
{
public:
	static SkeletalBaron* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeySkeletalBaron;

private:
	SkeletalBaron(cocos2d::ValueMap* initProperties);
	~SkeletalBaron();
};
