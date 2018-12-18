////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Finch : public NpcBase
{
public:
	static Finch* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyFinch;

private:
	Finch(cocos2d::ValueMap* initProperties);
	~Finch();
};
