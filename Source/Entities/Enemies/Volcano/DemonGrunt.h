#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class DemonGrunt : public Enemy
{
public:
	static DemonGrunt * create();

	static const std::string KeyEnemyDemonGrunt;

private:
	DemonGrunt();
	~DemonGrunt();
};
