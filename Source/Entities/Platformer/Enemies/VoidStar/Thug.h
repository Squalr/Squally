////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Thug : public PlatformerEnemy
{
public:
	static Thug* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyThug;

private:
	Thug(cocos2d::ValueMap& initProperties);
	~Thug();
};
