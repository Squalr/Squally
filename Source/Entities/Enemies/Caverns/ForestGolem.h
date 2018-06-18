#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class ForestGolem : public Enemy
{
public:
	static ForestGolem * create();

	static const std::string KeyEnemyForestGolem;

private:
	ForestGolem();
	~ForestGolem();
};
