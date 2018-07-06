#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossDemonKing : public PlatformerEnemy
{
public:
	static BossDemonKing * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyBossDemonKing;

private:
	BossDemonKing(ValueMap* initProperties);
	~BossDemonKing();
};
