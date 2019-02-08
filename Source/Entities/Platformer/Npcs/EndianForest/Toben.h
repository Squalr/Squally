////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Toben : public NpcBase
{
public:
	static Toben* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyToben;

private:
	Toben(cocos2d::ValueMap& initProperties);
	~Toben();
};
