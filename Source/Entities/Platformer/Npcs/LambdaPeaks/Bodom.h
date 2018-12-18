////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Bodom : public NpcBase
{
public:
	static Bodom* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyBodom;

private:
	Bodom(cocos2d::ValueMap* initProperties);
	~Bodom();
};
