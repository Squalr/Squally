////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Thurstan : public NpcBase
{
public:
	static Thurstan* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyThurstan;

private:
	Thurstan(cocos2d::ValueMap* initProperties);
	~Thurstan();
};
