#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class TigerMan : public Enemy
{
public:
	static TigerMan * create();

	static const std::string KeyEnemyTigerMan;

private:
	TigerMan();
	~TigerMan();
};
