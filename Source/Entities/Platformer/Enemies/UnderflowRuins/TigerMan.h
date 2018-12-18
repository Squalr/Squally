////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class TigerMan : public PlatformerEnemy
{
public:
	static TigerMan* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyTigerMan;

private:
	TigerMan(cocos2d::ValueMap* initProperties);
	~TigerMan();
};
