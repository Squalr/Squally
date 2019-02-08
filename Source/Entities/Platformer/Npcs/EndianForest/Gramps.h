////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Gramps : public NpcBase
{
public:
	static Gramps* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyGramps;

private:
	Gramps(cocos2d::ValueMap& initProperties);
	~Gramps();
};
