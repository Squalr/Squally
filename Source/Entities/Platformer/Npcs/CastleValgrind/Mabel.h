////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Mabel : public NpcBase
{
public:
	static Mabel* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyMabel;

private:
	Mabel(cocos2d::ValueMap& initProperties);
	~Mabel();
};
