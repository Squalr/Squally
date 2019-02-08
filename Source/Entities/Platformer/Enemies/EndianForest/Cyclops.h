////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Cyclops : public PlatformerEnemy
{
public:
	static Cyclops* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCyclops;

private:
	Cyclops(cocos2d::ValueMap& initProperties);
	~Cyclops();
};
