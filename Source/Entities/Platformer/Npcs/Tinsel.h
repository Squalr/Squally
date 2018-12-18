////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Tinsel : public NpcBase
{
public:
	static Tinsel* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyTinsel;

private:
	Tinsel(cocos2d::ValueMap* initProperties);
	~Tinsel();
};
