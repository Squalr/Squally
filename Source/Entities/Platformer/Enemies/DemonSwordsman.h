////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class DemonSwordsman : public PlatformerEnemy
{
public:
	static DemonSwordsman* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyDemonSwordsman;

private:
	DemonSwordsman(cocos2d::ValueMap* initProperties);
	~DemonSwordsman();
};
