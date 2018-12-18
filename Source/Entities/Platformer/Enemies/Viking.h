////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Viking : public PlatformerEnemy
{
public:
	static Viking* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyViking;

private:
	Viking(cocos2d::ValueMap* initProperties);
	~Viking();
};
