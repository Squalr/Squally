////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Rhinoman : public PlatformerEnemy
{
public:
	static Rhinoman* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyRhinoman;

private:
	Rhinoman(cocos2d::ValueMap& initProperties);
	~Rhinoman();
};
