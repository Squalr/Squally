////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Robin : public NpcBase
{
public:
	static Robin* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyRobin;

private:
	Robin(cocos2d::ValueMap& initProperties);
	~Robin();
};
