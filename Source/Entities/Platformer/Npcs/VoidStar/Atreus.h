////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Atreus : public NpcBase
{
public:
	static Atreus* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyAtreus;

private:
	Atreus(cocos2d::ValueMap* initProperties);
	~Atreus();
};
