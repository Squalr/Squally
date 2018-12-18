////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Undead : public PlatformerEnemy
{
public:
	static Undead* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyUndead;

private:
	Undead(cocos2d::ValueMap* initProperties);
	~Undead();
};
