#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class KingRedsongSlime : public NpcBase
{
public:
	static KingRedsongSlime * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyKingRedsongSlime;

private:
	KingRedsongSlime(ValueMap* initProperties);
	~KingRedsongSlime();
};
