////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Wraith : public PlatformerEnemy
{
public:
	static Wraith* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyWraith;

private:
	Wraith(cocos2d::ValueMap* initProperties);
	~Wraith();
};
