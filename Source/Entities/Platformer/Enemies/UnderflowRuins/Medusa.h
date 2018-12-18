////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Medusa : public PlatformerEnemy
{
public:
	static Medusa* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyMedusa;

private:
	Medusa(cocos2d::ValueMap* initProperties);
	~Medusa();
};
