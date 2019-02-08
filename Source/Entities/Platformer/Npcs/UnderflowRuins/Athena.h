////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Athena : public NpcBase
{
public:
	static Athena* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyAthena;

private:
	Athena(cocos2d::ValueMap& initProperties);
	~Athena();
};
