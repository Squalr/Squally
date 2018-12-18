////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Genie : public PlatformerEnemy
{
public:
	static Genie* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyGenie;

private:
	Genie(cocos2d::ValueMap* initProperties);
	~Genie();
};
