////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Dudly : public NpcBase
{
public:
	static Dudly* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyDudly;

private:
	Dudly(cocos2d::ValueMap* initProperties);
	~Dudly();
};
