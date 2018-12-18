////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Ent : public PlatformerEnemy
{
public:
	static Ent* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyEnt;

private:
	Ent(cocos2d::ValueMap* initProperties);
	~Ent();
};
