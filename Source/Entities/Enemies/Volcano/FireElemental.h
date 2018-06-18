#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class FireElemental : public Enemy
{
public:
	static FireElemental * create();

	static const std::string KeyEnemyFireElemental;

private:
	FireElemental();
	~FireElemental();
};
