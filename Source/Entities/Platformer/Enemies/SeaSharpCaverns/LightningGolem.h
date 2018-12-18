////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LightningGolem : public PlatformerEnemy
{
public:
	static LightningGolem* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyLightningGolem;

private:
	LightningGolem(cocos2d::ValueMap* initProperties);
	~LightningGolem();
};
