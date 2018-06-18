#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class DarkDragon : public Enemy
{
public:
	static DarkDragon * create();

	static const std::string KeyEnemyDarkDragon;

private:
	DarkDragon();
	~DarkDragon();
};
