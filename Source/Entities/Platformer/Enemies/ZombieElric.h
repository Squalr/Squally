////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class ZombieElric : public PlatformerEnemy
{
public:
	static ZombieElric* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyZombieElric;

private:
	ZombieElric(cocos2d::ValueMap* initProperties);
	~ZombieElric();
};
