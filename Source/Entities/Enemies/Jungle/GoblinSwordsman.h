#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinSwordsman : public Enemy
{
public:
	static GoblinSwordsman * create();

private:
	GoblinSwordsman();
	~GoblinSwordsman();
};
