////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class MechDog : public PlatformerEnemy
{
public:
	static MechDog* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyMechDog;

private:
	MechDog(cocos2d::ValueMap* initProperties);
	~MechDog();
};
