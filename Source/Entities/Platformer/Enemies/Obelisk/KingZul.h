#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class KingZul : public PlatformerEnemy
{
public:
	static KingZul * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyKingZul;

private:
	KingZul(ValueMap* initProperties);
	~KingZul();
};
