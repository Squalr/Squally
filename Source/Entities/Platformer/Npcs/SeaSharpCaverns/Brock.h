////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Brock : public NpcBase
{
public:
	static Brock* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyBrock;

private:
	Brock(cocos2d::ValueMap* initProperties);
	~Brock();
};
