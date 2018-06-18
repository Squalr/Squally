#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Mantis : public Enemy
{
public:
	static Mantis * create();

	static const std::string KeyEnemyMantis;

private:
	Mantis();
	~Mantis();
};
