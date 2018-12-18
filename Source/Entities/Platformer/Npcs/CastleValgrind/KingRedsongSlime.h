////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class KingRedsongSlime : public NpcBase
{
public:
	static KingRedsongSlime* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyKingRedsongSlime;

private:
	KingRedsongSlime(cocos2d::ValueMap* initProperties);
	~KingRedsongSlime();
};
