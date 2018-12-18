////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class MiteBot : public PlatformerEnemy
{
public:
	static MiteBot* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyMiteBot;

private:
	MiteBot(cocos2d::ValueMap* initProperties);
	~MiteBot();
};
