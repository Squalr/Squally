////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Leon : public NpcBase
{
public:
	static Leon* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyLeon;

private:
	Leon(cocos2d::ValueMap* initProperties);
	~Leon();
};
