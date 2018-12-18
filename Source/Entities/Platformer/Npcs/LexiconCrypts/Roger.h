////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Roger : public NpcBase
{
public:
	static Roger* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyRoger;

private:
	Roger(cocos2d::ValueMap* initProperties);
	~Roger();
};
