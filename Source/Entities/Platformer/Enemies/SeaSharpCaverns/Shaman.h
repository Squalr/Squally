////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Shaman : public PlatformerEnemy
{
public:
	static Shaman* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyShaman;

private:
	Shaman(cocos2d::ValueMap& initProperties);
	~Shaman();
};
