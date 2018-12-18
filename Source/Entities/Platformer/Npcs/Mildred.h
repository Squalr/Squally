////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Mildred : public NpcBase
{
public:
	static Mildred* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyMildred;

private:
	Mildred(cocos2d::ValueMap* initProperties);
	~Mildred();
};
