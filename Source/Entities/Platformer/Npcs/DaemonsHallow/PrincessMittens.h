////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class PrincessMittens : public NpcBase
{
public:
	static PrincessMittens* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyPrincessMittens;

private:
	PrincessMittens(cocos2d::ValueMap* initProperties);
	~PrincessMittens();
};
