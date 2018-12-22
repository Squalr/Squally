////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class Knight : public PlatformerEntity
{
public:
	static Knight* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyKnight;

private:
	Knight(cocos2d::ValueMap* initProperties);
	~Knight();
};
