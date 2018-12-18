////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

namespace cocos2d
{
	class ValueMap;
}

class Abomination : public PlatformerEnemy
{
public:
	static Abomination* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyAbomination;

private:
	Abomination(cocos2d::ValueMap* initProperties);
	Abomination();
};
