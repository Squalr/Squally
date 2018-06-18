#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Jack : public Enemy
{
public:
	static Jack * create();

	static const std::string KeyEnemyJack;

private:
	Jack();
	~Jack();
};
