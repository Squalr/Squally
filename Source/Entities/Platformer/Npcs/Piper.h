////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Piper : public NpcBase
{
public:
	static Piper* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyPiper;

private:
	Piper(cocos2d::ValueMap* initProperties);
	~Piper();
};
