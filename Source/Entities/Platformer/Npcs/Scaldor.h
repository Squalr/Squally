////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Scaldor : public NpcBase
{
public:
	static Scaldor* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyScaldor;

private:
	Scaldor(cocos2d::ValueMap* initProperties);
	~Scaldor();
};
