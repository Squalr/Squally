////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Asmodeus : public PlatformerEnemy
{
public:
	static Asmodeus* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyAsmodeus;

private:
	Asmodeus(cocos2d::ValueMap* initProperties);
	~Asmodeus();
};
