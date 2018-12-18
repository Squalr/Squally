////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Ogre : public PlatformerEnemy
{
public:
	static Ogre* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyOgre;

private:
	Ogre(cocos2d::ValueMap* initProperties);
	~Ogre();
};
