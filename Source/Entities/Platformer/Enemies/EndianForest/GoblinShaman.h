////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class GoblinShaman : public PlatformerEnemy
{
public:
	static GoblinShaman* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyGoblinShaman;

private:
	GoblinShaman(cocos2d::ValueMap& initProperties);
	~GoblinShaman();
};
