////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class CritterDemon : public PlatformerEnemy
{
public:
	static CritterDemon* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCritterDemon;

private:
	CritterDemon(cocos2d::ValueMap& initProperties);
	~CritterDemon();
};
