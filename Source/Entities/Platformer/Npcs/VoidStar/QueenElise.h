////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class QueenElise : public NpcBase
{
public:
	static QueenElise* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyQueenElise;

private:
	QueenElise(cocos2d::ValueMap* initProperties);
	~QueenElise();
};
