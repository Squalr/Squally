#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class KingRedsong : public NpcBase
{
public:
	static KingRedsong* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcKingRedsong;

private:
	KingRedsong(ValueMap* initProperties);
	~KingRedsong();
};
