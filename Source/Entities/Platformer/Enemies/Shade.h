////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Shade : public PlatformerEnemy
{
public:
	static Shade* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyShade;

private:
	Shade(cocos2d::ValueMap* initProperties);
	~Shade();
};
