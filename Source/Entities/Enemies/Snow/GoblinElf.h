#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinElf : public Enemy
{
public:
	static GoblinElf * create();

	static const std::string KeyEnemyGoblinElf;

private:
	GoblinElf();
	~GoblinElf();
};
