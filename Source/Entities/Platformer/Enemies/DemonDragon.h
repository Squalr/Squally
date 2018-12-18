////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class DemonDragon : public PlatformerEnemy
{
public:
	static DemonDragon* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyDemonDragon;

private:
	DemonDragon(cocos2d::ValueMap* initProperties);
	~DemonDragon();
};
