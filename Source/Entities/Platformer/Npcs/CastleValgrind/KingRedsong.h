////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class KingRedsong : public NpcBase
{
public:
	static KingRedsong* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyKingRedsong;

private:
	KingRedsong(cocos2d::ValueMap& initProperties);
	~KingRedsong();
};
