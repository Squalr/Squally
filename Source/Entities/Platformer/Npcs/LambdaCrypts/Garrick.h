////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Garrick : public NpcBase
{
public:
	static Garrick* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyGarrick;

private:
	Garrick(cocos2d::ValueMap& initProperties);
	~Garrick();
};
