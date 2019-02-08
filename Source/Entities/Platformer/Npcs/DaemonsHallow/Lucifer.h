////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Lucifer : public NpcBase
{
public:
	static Lucifer* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyLucifer;

private:
	Lucifer(cocos2d::ValueMap& initProperties);
	~Lucifer();
};
