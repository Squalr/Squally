#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class GoblinSwordsman : public Enemy
{
public:
	static GoblinSwordsman * create();

private:
	GoblinSwordsman();
	~GoblinSwordsman();
};
