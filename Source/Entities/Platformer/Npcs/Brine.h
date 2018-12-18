////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Brine : public NpcBase
{
public:
	static Brine* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyBrine;

private:
	Brine(cocos2d::ValueMap* initProperties);
	~Brine();
};
