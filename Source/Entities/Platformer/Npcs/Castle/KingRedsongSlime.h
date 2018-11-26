#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class KingRedsongSlime : public NpcBase
{
public:
	static KingRedsongSlime* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcKingRedsongSlime;

private:
	KingRedsongSlime(ValueMap* initProperties);
	~KingRedsongSlime();
};
