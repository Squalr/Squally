////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class GoblinWarriorPig : public PlatformerEnemy
{
public:
	static GoblinWarriorPig* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyGoblinWarriorPig;

private:
	GoblinWarriorPig(cocos2d::ValueMap* initProperties);
	~GoblinWarriorPig();
};
