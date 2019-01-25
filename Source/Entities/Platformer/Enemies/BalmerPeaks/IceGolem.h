////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class IceGolem : public PlatformerEnemy
{
public:
	static IceGolem* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyIceGolem;

private:
	IceGolem(cocos2d::ValueMap* initProperties);
	~IceGolem();
};
