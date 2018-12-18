////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Juniper : public NpcBase
{
public:
	static Juniper* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyJuniper;

private:
	Juniper(cocos2d::ValueMap* initProperties);
	~Juniper();
};
