////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Amelia : public NpcBase
{
public:
	static Amelia* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyAmelia;

private:
	Amelia(cocos2d::ValueMap* initProperties);
	~Amelia();
};
