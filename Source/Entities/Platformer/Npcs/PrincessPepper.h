////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class PrincessPepper : public NpcBase
{
public:
	static PrincessPepper* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyPrincessPepper;

private:
	PrincessPepper(cocos2d::ValueMap* initProperties);
	~PrincessPepper();
};
