#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossDragonOrcKing : public PlatformerEnemy
{
public:
	static BossDragonOrcKing * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyBossDragonOrcKing;

private:
	BossDragonOrcKing(ValueMap* initProperties);
	~BossDragonOrcKing();
};
