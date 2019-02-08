////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class Vampiress : public PlatformerEnemy
{
public:
	static Vampiress* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyVampiress;

private:
	Vampiress(cocos2d::ValueMap& initProperties);
	~Vampiress();
};
