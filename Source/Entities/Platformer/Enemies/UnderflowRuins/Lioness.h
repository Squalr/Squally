////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Lioness : public PlatformerEnemy
{
public:
	static Lioness* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyLioness;

private:
	Lioness(cocos2d::ValueMap* initProperties);
	~Lioness();
};
