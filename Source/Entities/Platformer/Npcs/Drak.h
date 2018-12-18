////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Drak : public NpcBase
{
public:
	static Drak* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyDrak;

private:
	Drak(cocos2d::ValueMap* initProperties);
	~Drak();
};
