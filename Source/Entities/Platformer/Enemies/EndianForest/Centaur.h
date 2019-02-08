////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Centaur : public PlatformerEnemy
{
public:
	static Centaur* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCentaur;

private:
	Centaur(cocos2d::ValueMap& initProperties);
	~Centaur();
};
