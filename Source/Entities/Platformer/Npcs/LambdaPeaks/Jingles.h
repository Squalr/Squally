////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Jingles : public NpcBase
{
public:
	static Jingles* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyJingles;

private:
	Jingles(cocos2d::ValueMap* initProperties);
	~Jingles();
};
