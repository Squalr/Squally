#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinElf : public Enemy
{
public:
	static GoblinElf * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyGoblinElf;

private:
	GoblinElf(ValueMap* initProperties);
	~GoblinElf();
};
