////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Leroy : public NpcBase
{
public:
	static Leroy* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyLeroy;

private:
	Leroy(cocos2d::ValueMap* initProperties);
	~Leroy();
};
