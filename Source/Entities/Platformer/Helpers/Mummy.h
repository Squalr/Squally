////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class Mummy : public PlatformerEntity
{
public:
	static Mummy* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyMummy;

private:
	Mummy(cocos2d::ValueMap& initProperties);
	~Mummy();
};
