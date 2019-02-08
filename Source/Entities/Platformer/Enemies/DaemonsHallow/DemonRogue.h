////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class DemonRogue : public PlatformerEnemy
{
public:
	static DemonRogue* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyDemonRogue;

private:
	DemonRogue(cocos2d::ValueMap& initProperties);
	~DemonRogue();
};
