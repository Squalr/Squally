////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Ursula : public NpcBase
{
public:
	static Ursula* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyUrsula;

private:
	Ursula(cocos2d::ValueMap* initProperties);
	~Ursula();
};
