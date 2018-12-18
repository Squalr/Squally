////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Executioner : public PlatformerEnemy
{
public:
	static Executioner* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyExecutioner;

private:
	Executioner(cocos2d::ValueMap* initProperties);
	~Executioner();
};
