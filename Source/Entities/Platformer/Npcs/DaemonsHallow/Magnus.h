////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Magnus : public NpcBase
{
public:
	static Magnus* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyMagnus;

private:
	Magnus(cocos2d::ValueMap& initProperties);
	~Magnus();
};
