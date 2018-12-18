////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Celeste : public NpcBase
{
public:
	static Celeste* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyCeleste;

private:
	Celeste(cocos2d::ValueMap* initProperties);
	~Celeste();
};
