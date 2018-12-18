////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class PrincessMatu : public NpcBase
{
public:
	static PrincessMatu* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyPrincessMatu;

private:
	PrincessMatu(cocos2d::ValueMap* initProperties);
	~PrincessMatu();
};
