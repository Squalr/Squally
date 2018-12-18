////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Hera : public NpcBase
{
public:
	static Hera* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyHera;

private:
	Hera(cocos2d::ValueMap* initProperties);
	~Hera();
};
