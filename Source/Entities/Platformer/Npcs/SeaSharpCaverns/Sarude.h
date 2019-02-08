////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Sarude : public NpcBase
{
public:
	static Sarude* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeySarude;

private:
	Sarude(cocos2d::ValueMap& initProperties);
	~Sarude();
};
