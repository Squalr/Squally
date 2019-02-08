////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Raka : public NpcBase
{
public:
	static Raka* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyRaka;

private:
	Raka(cocos2d::ValueMap& initProperties);
	~Raka();
};
