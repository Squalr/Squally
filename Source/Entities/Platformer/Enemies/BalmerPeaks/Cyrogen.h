////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Cyrogen : public PlatformerEnemy
{
public:
	static Cyrogen* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCyrogen;

private:
	Cyrogen(cocos2d::ValueMap& initProperties);
	~Cyrogen();
};
