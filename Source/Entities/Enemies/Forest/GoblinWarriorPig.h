#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinWarriorPig : public Enemy
{
public:
	static GoblinWarriorPig * create();

private:
	GoblinWarriorPig();
	~GoblinWarriorPig();
};
