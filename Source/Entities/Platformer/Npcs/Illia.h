////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Illia : public NpcBase
{
public:
	static Illia* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyIllia;

private:
	Illia(cocos2d::ValueMap* initProperties);
	~Illia();
};
