////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class MummyPriest : public PlatformerEnemy
{
public:
	static MummyPriest* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyMummyPriest;

private:
	MummyPriest(cocos2d::ValueMap* initProperties);
	~MummyPriest();
};
