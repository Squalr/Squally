////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class PenguinWarrior : public PlatformerEnemy
{
public:
	static PenguinWarrior* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyPenguinWarrior;

private:
	PenguinWarrior(cocos2d::ValueMap& initProperties);
	~PenguinWarrior();
};
