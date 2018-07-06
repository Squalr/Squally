#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinGuard : public PlatformerEnemy
{
public:
	static GoblinGuard * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyGoblinGuard;

private:
	GoblinGuard(ValueMap* initProperties);
	~GoblinGuard();
};
