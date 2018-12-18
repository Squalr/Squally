////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class VikingBot : public PlatformerEnemy
{
public:
	static VikingBot* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyVikingBot;

private:
	VikingBot(cocos2d::ValueMap* initProperties);
	~VikingBot();
};
