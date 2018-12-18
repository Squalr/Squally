////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class EvilEye : public PlatformerEnemy
{
public:
	static EvilEye* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyEvilEye;

private:
	EvilEye(cocos2d::ValueMap* initProperties);
	~EvilEye();
};
