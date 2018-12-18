////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Radon : public NpcBase
{
public:
	static Radon* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyRadon;

private:
	Radon(cocos2d::ValueMap* initProperties);
	~Radon();
};
