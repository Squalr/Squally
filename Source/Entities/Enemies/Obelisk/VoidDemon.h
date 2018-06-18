#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class VoidDemon : public Enemy
{
public:
	static VoidDemon * create();

	static const std::string KeyEnemyVoidDemon;

private:
	VoidDemon();
	~VoidDemon();
};
