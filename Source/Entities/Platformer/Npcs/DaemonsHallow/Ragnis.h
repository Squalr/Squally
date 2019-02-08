////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Ragnis : public NpcBase
{
public:
	static Ragnis* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyRagnis;

private:
	Ragnis(cocos2d::ValueMap& initProperties);
	~Ragnis();
};
