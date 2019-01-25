////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class PenguinGrunt : public PlatformerEnemy
{
public:
	static PenguinGrunt* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyPenguinGrunt;

private:
	PenguinGrunt(cocos2d::ValueMap* initProperties);
	~PenguinGrunt();
};
