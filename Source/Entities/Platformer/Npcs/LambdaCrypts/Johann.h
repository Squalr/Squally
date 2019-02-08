////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Johann : public NpcBase
{
public:
	static Johann* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyJohann;

private:
	Johann(cocos2d::ValueMap& initProperties);
	~Johann();
};
