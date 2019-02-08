////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Griffin : public NpcBase
{
public:
	static Griffin* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyGriffin;

private:
	Griffin(cocos2d::ValueMap& initProperties);
	~Griffin();
};
