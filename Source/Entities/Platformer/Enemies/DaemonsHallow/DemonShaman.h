////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class DemonShaman : public PlatformerEnemy
{
public:
	static DemonShaman* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyDemonShaman;

private:
	DemonShaman(cocos2d::ValueMap& initProperties);
	~DemonShaman();
};
