#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class MechGolem : public Enemy
{
public:
	static MechGolem * create();

	static const std::string KeyEnemyMechGolem;

private:
	MechGolem();
	~MechGolem();
};
