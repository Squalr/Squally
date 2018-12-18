////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Minotaur : public PlatformerEnemy
{
public:
	static Minotaur* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyMinotaur;

private:
	Minotaur(cocos2d::ValueMap* initProperties);
	~Minotaur();
};
