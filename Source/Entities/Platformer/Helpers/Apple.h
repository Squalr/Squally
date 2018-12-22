////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class Apple : public PlatformerEntity
{
public:
	static Apple* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyApple;

private:
	Apple(cocos2d::ValueMap* initProperties);
	~Apple();
};
