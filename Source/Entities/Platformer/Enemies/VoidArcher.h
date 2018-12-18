////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class VoidArcher : public PlatformerEnemy
{
public:
	static VoidArcher* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyVoidArcher;

private:
	VoidArcher(cocos2d::ValueMap* initProperties);
	~VoidArcher();
};
