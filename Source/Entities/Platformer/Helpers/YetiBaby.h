////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class YetiBaby : public PlatformerEntity
{
public:
	static YetiBaby* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyYetiBaby;

private:
	YetiBaby(cocos2d::ValueMap& initProperties);
	~YetiBaby();
};
