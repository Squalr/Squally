////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class DemonGrunt : public PlatformerEnemy
{
public:
	static DemonGrunt* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyDemonGrunt;

private:
	DemonGrunt(cocos2d::ValueMap* initProperties);
	~DemonGrunt();
};
