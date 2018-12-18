////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class PrincessNebea : public NpcBase
{
public:
	static PrincessNebea* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyPrincessNebea;

private:
	PrincessNebea(cocos2d::ValueMap* initProperties);
	~PrincessNebea();
};
