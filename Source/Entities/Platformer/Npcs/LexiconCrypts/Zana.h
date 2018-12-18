////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Zana : public NpcBase
{
public:
	static Zana* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyZana;

private:
	Zana(cocos2d::ValueMap* initProperties);
	~Zana();
};
