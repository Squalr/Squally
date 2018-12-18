////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Aphrodite : public NpcBase
{
public:
	static Aphrodite* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyAphrodite;

private:
	Aphrodite(cocos2d::ValueMap* initProperties);
	~Aphrodite();
};
