////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class Turtle : public PlatformerEntity
{
public:
	static Turtle* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyTurtle;

private:
	Turtle(cocos2d::ValueMap* initProperties);
	~Turtle();
};
