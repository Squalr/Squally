////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Blackbeard : public NpcBase
{
public:
	static Blackbeard* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyBlackbeard;

private:
	Blackbeard(cocos2d::ValueMap& initProperties);
	~Blackbeard();
};
