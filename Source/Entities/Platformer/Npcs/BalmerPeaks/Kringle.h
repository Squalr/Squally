////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Kringle : public NpcBase
{
public:
	static Kringle* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyKringle;

private:
	Kringle(cocos2d::ValueMap& initProperties);
	~Kringle();
};
