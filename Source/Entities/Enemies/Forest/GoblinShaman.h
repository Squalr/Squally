#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinShaman : public Enemy
{
public:
	static GoblinShaman * create();

	static const std::string KeyEnemyGoblinShaman;

private:
	GoblinShaman();
	~GoblinShaman();
};
