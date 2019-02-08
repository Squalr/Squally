////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Yeti : public PlatformerEnemy
{
public:
	static Yeti* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyYeti;

private:
	Yeti(cocos2d::ValueMap& initProperties);
	~Yeti();
};
