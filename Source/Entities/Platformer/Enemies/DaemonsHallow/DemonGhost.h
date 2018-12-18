////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class DemonGhost : public PlatformerEnemy
{
public:
	static DemonGhost* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyDemonGhost;

private:
	DemonGhost(cocos2d::ValueMap* initProperties);
	~DemonGhost();
};
