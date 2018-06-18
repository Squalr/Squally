#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossDemonKing : public Enemy
{
public:
	static BossDemonKing * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyBossDemonKing;

private:
	BossDemonKing(ValueMap* initProperties);
	~BossDemonKing();
};
