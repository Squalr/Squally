////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class BlackWidow : public PlatformerEnemy
{
public:
	static BlackWidow* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyBlackWidow;

private:
	BlackWidow(cocos2d::ValueMap& initProperties);
	~BlackWidow();
};
