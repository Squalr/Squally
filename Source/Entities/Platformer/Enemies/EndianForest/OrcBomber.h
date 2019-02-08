////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class OrcBomber : public PlatformerEnemy
{
public:
	static OrcBomber* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyOrcBomber;

private:
	OrcBomber(cocos2d::ValueMap& initProperties);
	~OrcBomber();
};
