////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Zeus : public NpcBase
{
public:
	static Zeus* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyZeus;

private:
	Zeus(cocos2d::ValueMap& initProperties);
	~Zeus();
};
