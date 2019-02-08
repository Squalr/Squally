////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class GoblinGruntBoar : public PlatformerEnemy
{
public:
	static GoblinGruntBoar* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyGoblinGruntBoar;

private:
	GoblinGruntBoar(cocos2d::ValueMap& initProperties);
	~GoblinGruntBoar();
};
