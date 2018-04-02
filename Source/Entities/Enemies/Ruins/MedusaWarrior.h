#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class MedusaWarrior : public Enemy
{
public:
	static MedusaWarrior * create();

private:
	MedusaWarrior();
	~MedusaWarrior();
};
