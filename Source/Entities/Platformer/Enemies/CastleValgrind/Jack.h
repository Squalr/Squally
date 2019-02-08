////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Jack : public PlatformerEnemy
{
public:
	static Jack* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyJack;

private:
	Jack(cocos2d::ValueMap& initProperties);
	~Jack();
};
