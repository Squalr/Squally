////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Azmus : public NpcBase
{
public:
	static Azmus* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyAzmus;

private:
	Azmus(cocos2d::ValueMap* initProperties);
	~Azmus();
};
