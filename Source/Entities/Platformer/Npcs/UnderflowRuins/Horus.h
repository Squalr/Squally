////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Horus : public NpcBase
{
public:
	static Horus* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyHorus;

private:
	Horus(cocos2d::ValueMap* initProperties);
	~Horus();
};
