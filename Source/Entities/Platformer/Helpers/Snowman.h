////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class Snowman : public PlatformerEntity
{
public:
	static Snowman* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeySnowman;

private:
	Snowman(cocos2d::ValueMap* initProperties);
	~Snowman();
};
