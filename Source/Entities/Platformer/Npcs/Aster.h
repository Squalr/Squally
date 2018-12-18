////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Aster : public NpcBase
{
public:
	static Aster* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyAster;

private:
	Aster(cocos2d::ValueMap* initProperties);
	~Aster();
};
