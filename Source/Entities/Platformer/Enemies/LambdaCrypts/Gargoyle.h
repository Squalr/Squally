////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Gargoyle : public PlatformerEnemy
{
public:
	static Gargoyle* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyGargoyle;

private:
	Gargoyle(cocos2d::ValueMap& initProperties);
	~Gargoyle();
};
