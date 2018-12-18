////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Marcel : public NpcBase
{
public:
	static Marcel* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyMarcel;

private:
	Marcel(cocos2d::ValueMap* initProperties);
	~Marcel();
};
