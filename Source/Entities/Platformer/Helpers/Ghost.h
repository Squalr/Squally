////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class Ghost : public PlatformerEntity
{
public:
	static Ghost* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyGhost;

private:
	Ghost(cocos2d::ValueMap* initProperties);
	~Ghost();
};
