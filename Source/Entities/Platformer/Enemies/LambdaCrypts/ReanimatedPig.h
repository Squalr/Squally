////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class ReanimatedPig : public PlatformerEnemy
{
public:
	static ReanimatedPig* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyReanimatedPig;

private:
	ReanimatedPig(cocos2d::ValueMap& initProperties);
	~ReanimatedPig();
};
