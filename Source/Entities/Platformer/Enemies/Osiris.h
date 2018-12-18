////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Osiris : public PlatformerEnemy
{
public:
	static Osiris* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyOsiris;

private:
	Osiris(cocos2d::ValueMap* initProperties);
	~Osiris();
};
