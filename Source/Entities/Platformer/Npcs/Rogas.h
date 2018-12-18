////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Rogas : public NpcBase
{
public:
	static Rogas* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyRogas;

private:
	Rogas(cocos2d::ValueMap* initProperties);
	~Rogas();
};
