////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class PrincessOpal : public NpcBase
{
public:
	static PrincessOpal* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyPrincessOpal;

private:
	PrincessOpal(cocos2d::ValueMap* initProperties);
	~PrincessOpal();
};
