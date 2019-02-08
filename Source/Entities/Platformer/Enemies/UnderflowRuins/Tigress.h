////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Tigress : public PlatformerEnemy
{
public:
	static Tigress* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTigress;

private:
	Tigress(cocos2d::ValueMap& initProperties);
	~Tigress();
};
