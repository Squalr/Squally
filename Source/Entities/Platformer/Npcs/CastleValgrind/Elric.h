////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Elric : public NpcBase
{
public:
	static Elric* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyElric;

private:
	Elric(cocos2d::ValueMap* initProperties);
	~Elric();
};
