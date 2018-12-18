////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class OrcGrunt : public PlatformerEnemy
{
public:
	static OrcGrunt* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyOrcGrunt;

private:
	OrcGrunt(cocos2d::ValueMap* initProperties);
	~OrcGrunt();
};
