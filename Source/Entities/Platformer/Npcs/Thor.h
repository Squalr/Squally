////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Thor : public NpcBase
{
public:
	static Thor* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyThor;

private:
	Thor(cocos2d::ValueMap* initProperties);
	~Thor();
};
