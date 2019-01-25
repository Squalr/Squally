////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Santa : public PlatformerEnemy
{
public:
	static Santa* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeySanta;

private:
	Santa(cocos2d::ValueMap* initProperties);
	~Santa();
};
