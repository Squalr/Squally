////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class GoblinElf : public PlatformerEnemy
{
public:
	static GoblinElf* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyGoblinElf;

private:
	GoblinElf(cocos2d::ValueMap* initProperties);
	~GoblinElf();
};
