////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LavaGolem : public PlatformerEnemy
{
public:
	static LavaGolem* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyLavaGolem;

private:
	LavaGolem(cocos2d::ValueMap* initProperties);
	~LavaGolem();
};
