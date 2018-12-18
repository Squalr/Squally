////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Krampus : public PlatformerEnemy
{
public:
	static Krampus* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyKrampus;

private:
	Krampus(cocos2d::ValueMap* initProperties);
	~Krampus();
};
