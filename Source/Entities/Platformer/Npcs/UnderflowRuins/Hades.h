////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Hades : public NpcBase
{
public:
	static Hades* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyHades;

private:
	Hades(cocos2d::ValueMap* initProperties);
	~Hades();
};
