////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Rusty : public NpcBase
{
public:
	static Rusty* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyRusty;

private:
	Rusty(cocos2d::ValueMap* initProperties);
	~Rusty();
};
