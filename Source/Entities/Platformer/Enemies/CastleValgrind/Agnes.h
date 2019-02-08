////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Agnes : public PlatformerEnemy
{
public:
	static Agnes* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyAgnes;

private:
	Agnes(cocos2d::ValueMap& initProperties);
	~Agnes();
};
