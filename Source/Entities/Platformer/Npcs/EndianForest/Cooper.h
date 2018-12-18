////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Cooper : public NpcBase
{
public:
	static Cooper* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyCooper;

private:
	Cooper(cocos2d::ValueMap* initProperties);
	~Cooper();
};
