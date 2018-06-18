#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinGuard : public Enemy
{
public:
	static GoblinGuard * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyGoblinGuard;

private:
	GoblinGuard(ValueMap* initProperties);
	~GoblinGuard();
};
