////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class PrincessDawn : public NpcBase
{
public:
	static PrincessDawn* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyPrincessDawn;

private:
	PrincessDawn(cocos2d::ValueMap* initProperties);
	~PrincessDawn();
};
