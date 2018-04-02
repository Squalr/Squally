#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class OrcWarrior : public Enemy
{
public:
	static OrcWarrior * create();

private:
	OrcWarrior();
	~OrcWarrior();
};
