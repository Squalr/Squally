////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class MummyWarrior : public PlatformerEnemy
{
public:
	static MummyWarrior* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyMummyWarrior;

private:
	MummyWarrior(cocos2d::ValueMap* initProperties);
	~MummyWarrior();
};
