////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class SkeletalPirate : public PlatformerEnemy
{
public:
	static SkeletalPirate* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeySkeletalPirate;

private:
	SkeletalPirate(cocos2d::ValueMap* initProperties);
	~SkeletalPirate();
};
