////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class OrcWarrior : public PlatformerEnemy
{
public:
	static OrcWarrior* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyOrcWarrior;

private:
	OrcWarrior(cocos2d::ValueMap& initProperties);
	~OrcWarrior();
};
