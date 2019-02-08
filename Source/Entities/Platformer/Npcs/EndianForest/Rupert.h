////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Rupert : public NpcBase
{
public:
	static Rupert* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyRupert;

private:
	Rupert(cocos2d::ValueMap& initProperties);
	~Rupert();
};
