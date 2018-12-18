////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Fraya : public NpcBase
{
public:
	static Fraya* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyFraya;

private:
	Fraya(cocos2d::ValueMap* initProperties);
	~Fraya();
};
