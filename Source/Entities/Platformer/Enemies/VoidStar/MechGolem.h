////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class MechGolem : public PlatformerEnemy
{
public:
	static MechGolem* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyMechGolem;

private:
	MechGolem(cocos2d::ValueMap* initProperties);
	~MechGolem();
};
