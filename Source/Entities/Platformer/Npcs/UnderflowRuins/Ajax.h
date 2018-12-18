////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Ajax : public NpcBase
{
public:
	static Ajax* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyAjax;

private:
	Ajax(cocos2d::ValueMap* initProperties);
	~Ajax();
};
