////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Guard : public PlatformerEnemy
{
public:
	static Guard* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyGuard;

private:
	Guard(cocos2d::ValueMap& initProperties);
	~Guard();
};
