////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Reaper : public PlatformerEnemy
{
public:
	static Reaper* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyReaper;

private:
	Reaper(cocos2d::ValueMap* initProperties);
	~Reaper();
};
