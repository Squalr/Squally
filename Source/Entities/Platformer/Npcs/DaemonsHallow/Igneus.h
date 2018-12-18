////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Igneus : public NpcBase
{
public:
	static Igneus* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyIgneus;

private:
	Igneus(cocos2d::ValueMap* initProperties);
	~Igneus();
};
