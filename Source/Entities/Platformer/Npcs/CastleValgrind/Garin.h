////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Garin : public NpcBase
{
public:
	static Garin* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyGarin;

private:
	Garin(cocos2d::ValueMap& initProperties);
	~Garin();
};
