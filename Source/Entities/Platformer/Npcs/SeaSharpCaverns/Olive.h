////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Olive : public NpcBase
{
public:
	static Olive* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyOlive;

private:
	Olive(cocos2d::ValueMap& initProperties);
	~Olive();
};
