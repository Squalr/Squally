////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Aspen : public NpcBase
{
public:
	static Aspen* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyAspen;

private:
	Aspen(cocos2d::ValueMap* initProperties);
	~Aspen();
};
