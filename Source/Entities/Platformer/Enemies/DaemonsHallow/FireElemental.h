////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class FireElemental : public PlatformerEnemy
{
public:
	static FireElemental* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyFireElemental;

private:
	FireElemental(cocos2d::ValueMap& initProperties);
	~FireElemental();
};
