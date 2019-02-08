////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class Princess : public PlatformerEntity
{
public:
	static Princess* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyPrincess;

private:
	Princess(cocos2d::ValueMap& initProperties);
	~Princess();
};
