#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class VampireLord : public Enemy
{
public:
	static VampireLord * create();

	static const std::string KeyEnemyVampireLord;

private:
	VampireLord();
	~VampireLord();
};
