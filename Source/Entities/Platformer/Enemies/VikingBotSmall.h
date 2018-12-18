////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class VikingBotSmall : public PlatformerEnemy
{
public:
	static VikingBotSmall* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyVikingBotSmall;

private:
	VikingBotSmall(cocos2d::ValueMap* initProperties);
	~VikingBotSmall();
};
