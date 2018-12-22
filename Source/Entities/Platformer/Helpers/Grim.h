////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class Grim : public PlatformerEntity
{
public:
	static Grim* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyGrim;

private:
	Grim(cocos2d::ValueMap* initProperties);
	~Grim();
};
