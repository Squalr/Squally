////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Cleopatra : public NpcBase
{
public:
	static Cleopatra* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCleopatra;

private:
	Cleopatra(cocos2d::ValueMap& initProperties);
	~Cleopatra();
};
