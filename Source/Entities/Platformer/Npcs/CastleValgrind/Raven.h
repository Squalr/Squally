////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Raven : public NpcBase
{
public:
	static Raven* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyRaven;

private:
	Raven(cocos2d::ValueMap* initProperties);
	~Raven();
};
