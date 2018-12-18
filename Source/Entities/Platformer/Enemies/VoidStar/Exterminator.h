////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Exterminator : public PlatformerEnemy
{
public:
	static Exterminator* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyExterminator;

private:
	Exterminator(cocos2d::ValueMap* initProperties);
	~Exterminator();
};
