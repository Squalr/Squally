////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Merlin : public NpcBase
{
public:
	static Merlin* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyMerlin;

private:
	Merlin(cocos2d::ValueMap& initProperties);
	~Merlin();
};
