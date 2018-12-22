////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class Robot : public PlatformerEntity
{
public:
	static Robot* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyRobot;

private:
	Robot(cocos2d::ValueMap* initProperties);
	~Robot();
};
