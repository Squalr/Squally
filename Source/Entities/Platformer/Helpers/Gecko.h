////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class Gecko : public PlatformerEntity
{
public:
	static Gecko* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyGecko;

private:
	Gecko(cocos2d::ValueMap& initProperties);
	~Gecko();
};
