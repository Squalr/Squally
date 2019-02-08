////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Barbarian : public PlatformerEnemy
{
public:
	static Barbarian* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyBarbarian;

private:
	Barbarian(cocos2d::ValueMap& initProperties);
	~Barbarian();
};
