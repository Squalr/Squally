////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class SkeletalKnight : public PlatformerEnemy
{
public:
	static SkeletalKnight* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeySkeletalKnight;

private:
	SkeletalKnight(cocos2d::ValueMap* initProperties);
	~SkeletalKnight();
};
