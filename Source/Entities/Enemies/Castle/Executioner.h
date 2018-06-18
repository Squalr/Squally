#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Executioner : public Enemy
{
public:
	static Executioner * create();

	static const std::string KeyEnemyExecutioner;

private:
	Executioner();
	~Executioner();
};
