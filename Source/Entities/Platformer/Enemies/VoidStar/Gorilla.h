////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Gorilla : public PlatformerEnemy
{
public:
	static Gorilla* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyGorilla;

private:
	Gorilla(cocos2d::ValueMap& initProperties);
	~Gorilla();
};
