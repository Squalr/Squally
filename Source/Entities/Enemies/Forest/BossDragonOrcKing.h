#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossDragonOrcKing : public Enemy
{
public:
	static BossDragonOrcKing * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyBossDragonOrcKing;

private:
	BossDragonOrcKing(ValueMap* initProperties);
	~BossDragonOrcKing();
};
